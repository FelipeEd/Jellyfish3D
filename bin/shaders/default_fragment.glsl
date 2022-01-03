#version 330 core

out vec4 FragColor;
in vec3 f_vertexColor;
in vec3 f_normal;
in vec2 f_texCoord;

uniform vec4 uColor;
uniform sampler2D ourTexture;

void main()
{
    //FragColor = vec4(normalize( (texture(ourTexture, f_texCoord)).xyz + f_vertexColor*0.01) * max(dot(f_normal,vec3(1.0,1.0,1.0)),0.3),1.0) ; 
    FragColor = vec4((uColor.xyz*(texture(ourTexture, f_texCoord)).xyz) * max(dot(f_normal,vec3(1.0,1.0,1.0)),0.3),1.0) ; 
} 