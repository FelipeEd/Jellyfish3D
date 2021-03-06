#version 330 core

out vec4 FragColor;

in vec3 f_normal;
in vec2 f_texCoord;
in vec3 f_worldPos;
//in mat3 f_TBN;

// material parameters
//uniform float uTexMetallic;
//uniform float uTexRoughness;
//uniform float uTexAo;

// // material parameters
uniform sampler2D uTexAlbedo;
uniform sampler2D uTexNormalMap;
uniform sampler2D uTexMetallic;
uniform sampler2D uTexRoughness;
uniform sampler2D uTexAo;
uniform samplerCube uSkyboxMap;
uniform samplerCube uIrradianceMap;
uniform samplerCube uRadianceMap;

// lights
uniform vec3 lightPositions[4];
uniform vec3 lightColors[4];

uniform vec3 uCamPos;
uniform vec4 uColor;

uniform bool uUseNormalmap;

const float PI = 3.14159265359;

vec3 getNormalFromMap();
float DistributionGGX(vec3 N, vec3 H, float roughness);
float GeometrySchlickGGX(float NdotV, float roughness);
float GeometrySmith(vec3 N, vec3 V, vec3 L, float roughness);
vec3 fresnelSchlick(float cosTheta, vec3 F0);
vec3 fresnelSchlickRoughness(float cosTheta, vec3 F0, float roughness);


void main()
{	
    // material properties
    vec3 albedo = pow(texture(uTexAlbedo, f_texCoord).rgb, vec3(2.2));
    float metallic = texture(uTexMetallic, f_texCoord).r;
    float roughness = texture(uTexRoughness, f_texCoord).r;
    float ao = texture(uTexAo, f_texCoord).r;

    //albedo = vec3(0.5,0.0,0.0);
    //metallic = 0.5;
    //roughness = 0.5;
    //ao = 1.0;
       
    // input lighting data
    vec3 N = normalize(f_normal);
    if(uUseNormalmap){
        vec4 a = uColor;
    }
    vec3 V = normalize(uCamPos - f_worldPos);
    vec3 R = reflect(-V, N); 

    // calculate reflectance at normal incidence; if dia-electric (like plastic) use F0 
    // of 0.04 and if it's a metal, use the albedo color as F0 (metallic workflow)    
    vec3 F0 = vec3(0.04); 
    F0 = mix(F0, albedo, metallic);

    // reflectance equation
    vec3 Lo = vec3(0.0);
    for(int i = 0; i < 4; ++i) 
    {
        // calculate per-light radiance
        vec3 L = normalize(lightPositions[i] - f_worldPos);
        vec3 H = normalize(V + L);
        float distance = length(lightPositions[i] - f_worldPos);
        float attenuation = 1.0 / (distance * distance);
        vec3 radiance = lightColors[i] * attenuation;

        // Cook-Torrance BRDF
        float NDF = DistributionGGX(N, H, roughness);   
        float G   = GeometrySmith(N, V, L, roughness);    
        vec3 F    = fresnelSchlick(max(dot(H, V), 0.0), F0);        
        
        vec3 numerator    = NDF * G * F;
        float denominator = 4.0 * max(dot(N, V), 0.0) * max(dot(N, L), 0.0) + 0.0001; // + 0.0001 to prevent divide by zero
        vec3 specular = numerator / denominator;
        
         // kS is equal to Fresnel
        vec3 kS = F;
        // for energy conservation, the diffuse and specular light can't
        // be above 1.0 (unless the surface emits light); to preserve this
        // relationship the diffuse component (kD) should equal 1.0 - kS.
        vec3 kD = vec3(1.0) - kS;
        // multiply kD by the inverse metalness such that only non-metals 
        // have diffuse lighting, or a linear blend if partly metal (pure metals
        // have no diffuse light).
        kD *= 1.0 - metallic;	                
            
        // scale light by NdotL
        float NdotL = max(dot(N, L), 0.0);        

        // add to outgoing radiance Lo
        Lo += (kD * albedo / PI + specular) * radiance * NdotL; // note that we already multiplied the BRDF by the Fresnel (kS) so we won't multiply by kS again
    }   
    
    // ambient lighting (we now use IBL as the ambient term)
    vec3 F = fresnelSchlickRoughness(max(dot(N, V), 0.0), F0, roughness);
    
    vec3 kS = F;
    vec3 kD = 1.0 - kS;
    kD *= 1.0 - metallic;	  
    
    vec3 irradiance = texture(uIrradianceMap, N).rgb ;
    vec3 diffuse      = irradiance * albedo;
    
    // sample both the pre-filter map and the BRDF lut and combine them together as per the Split-Sum approximation to get the IBL specular part.
    const float MAX_REFLECTION_LOD = 4.0;
    vec3 prefilteredColor = textureLod(uSkyboxMap, R,  roughness * MAX_REFLECTION_LOD).rgb;    
    //vec2 brdf  = texture(uRadianceMap, vec3(max(dot(N, V), 0.0), roughness,0.0)).rg;
    vec3 specular = prefilteredColor * F;//  * (F * brdf.x + brdf.y);

    vec3 ambient = (kD * diffuse + specular) * ao;
    
    vec3 color = ambient + Lo;// + texture(uRadianceMap,N).rgb * kS;

    // HDR tonemapping
    color = color / (color + vec3(1.0));
    // // gamma correct
    color = pow(color, vec3(1.0/1.8)); 

    FragColor = vec4(color , 1.0);
    
}  

vec3 getNormalFromMap()
{
    vec3 tangentNormal = texture(uTexNormalMap, f_texCoord).xyz * 2.0 - 1.0;

    vec3 Q1  = dFdx(f_worldPos);
    vec3 Q2  = dFdy(f_worldPos);
    vec2 st1 = dFdx(f_texCoord);
    vec2 st2 = dFdy(f_texCoord);

    vec3 N   = normalize(f_normal);
    vec3 T  = normalize(Q1*st2.t - Q2*st1.t);
    vec3 B  = -normalize(cross(N, T));
    mat3 TBN = mat3(T, B, N);

    return normalize(TBN * tangentNormal);
}
// ----------------------------------------------------------------------------
float DistributionGGX(vec3 N, vec3 H, float roughness)
{
    float a = roughness*roughness;
    float a2 = a*a;
    float NdotH = max(dot(N, H), 0.0);
    float NdotH2 = NdotH*NdotH;

    float nom   = a2;
    float denom = (NdotH2 * (a2 - 1.0) + 1.0);
    denom = PI * denom * denom;

    return nom / denom;
}
// ----------------------------------------------------------------------------
float GeometrySchlickGGX(float NdotV, float roughness)
{
    float r = (roughness + 1.0);
    float k = (r*r) / 8.0;

    float nom   = NdotV;
    float denom = NdotV * (1.0 - k) + k;

    return nom / denom;
}
// ----------------------------------------------------------------------------
float GeometrySmith(vec3 N, vec3 V, vec3 L, float roughness)
{
    float NdotV = max(dot(N, V), 0.0);
    float NdotL = max(dot(N, L), 0.0);
    float ggx2 = GeometrySchlickGGX(NdotV, roughness);
    float ggx1 = GeometrySchlickGGX(NdotL, roughness);

    return ggx1 * ggx2;
}
// ----------------------------------------------------------------------------
vec3 fresnelSchlick(float cosTheta, vec3 F0)
{
    return F0 + (1.0 - F0) * pow(clamp(1.0 - cosTheta, 0.0, 1.0), 5.0);
}
// ----------------------------------------------------------------------------
vec3 fresnelSchlickRoughness(float cosTheta, vec3 F0, float roughness)
{
    return F0 + (max(vec3(1.0 - roughness), F0) - F0) * pow(clamp(1.0 - cosTheta, 0.0, 1.0), 5.0);
}   
// ----------------------------------------------------------------------------