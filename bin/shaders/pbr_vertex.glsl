#version 330 core

// Location define a posição do atributo no VAO
layout (location = 0) in vec3 aPos;
layout (location = 1) in vec3 aColor;
layout (location = 2) in vec2 aTexCoord;
layout (location = 3) in vec3 aNormal;

//out vec3 f_vertexColor;
out vec3 f_normal;
out vec2 f_texCoord;
out vec3 f_worldPos;

uniform mat4 uModel;

uniform mat4 uView;
uniform mat4 uProjection;

uniform float uTime;
uniform bool uIsBoid;

void main()
{
    mat3 TBN = mat3(transpose(inverse(uModel)));
    //mat3 TBN =mat3(uModel);

    vec3 animPos = aPos;
    

    if(uIsBoid){
        float wingRange = radians(40.0);
        float theta = sin(uTime*5) * wingRange;
        

        if(animPos.x > 0){
            animPos.x = (cos(theta)* aPos.x + sin(theta)* aPos.y) ;
            animPos.y = (-sin(theta)* aPos.x + cos(theta)* aPos.y) ;
        }
        if(animPos.x < 0){
            animPos.x = (cos(-theta)* aPos.x + sin(-theta)* aPos.y) ;
            animPos.y = (-sin(-theta)* aPos.x + cos(-theta)* aPos.y) ;
        }
    }
    
    //f_TBN = TBN;
    f_normal = TBN * aNormal;
    // f_normal =  mat3(uModel) * aNormal; 
    f_texCoord = aTexCoord;
    
    f_worldPos = vec3(uModel * vec4(animPos, 1.0));

    gl_Position = uProjection * uView * uModel * vec4(animPos,1.0);
    
}
