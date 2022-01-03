#version 330 core

// Location define a posição do atributo no VAO
layout (location = 0) in vec3 aPos;
layout (location = 1) in vec3 aColor;
layout (location = 2) in vec2 aTexCoord;
layout (location = 3) in vec3 aNormal;

out vec3 f_vertexColor;
out vec3 f_normal;
out vec2 f_texCoord;

uniform mat4 uScale;
uniform mat4 uRotate;
uniform mat4 uTranslate;

uniform mat4 uView;
uniform mat4 uProjection;


void main()
{
    mat4 model =  uTranslate * uRotate * uScale;


    f_normal = mat3(transpose(inverse(model))) * aNormal; 
    f_texCoord = aTexCoord;
    //f_position = vec3(mvp * vec4(position, 1.0));

    //vec4 rotNormals = uTranslate * uRotate * uScale *vec4(aNormal,1.0);
    //normal = vec3(rotNormals.x,rotNormals.y,rotNormals.z);

    f_vertexColor = aColor;
    // gl_Position é uma das variaveis presentes no vertex shader
    // definirá a posição final do vértice
    // Deve ser um vec4 (X, Y, Z, W)
    gl_Position = uProjection * uView * model * vec4(aPos,1.0);
    
}
