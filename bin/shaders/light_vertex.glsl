#version 330 core

// Location define a posição do atributo no VAO
layout (location = 0) in vec3 aPos;
layout (location = 1) in vec3 aColor;
layout (location = 2) in vec2 aTexCoord;
layout (location = 3) in vec3 aNormal;

out vec3 f_vertexColor;
out vec3 f_normal;
out vec2 f_texCoord;

// uniform mat4 uScale;
// uniform mat4 uRotate;
// uniform mat4 uTranslate;uModel
uniform mat4 uModel;

uniform mat4 uView;
uniform mat4 uProjection;


void main()
{
    //mat4 model =  uTranslate * uRotate * uScale;


    f_normal = mat3(transpose(inverse(uModel))) * aNormal; 
    f_texCoord = aTexCoord;

    f_vertexColor = aColor;
    gl_Position = uProjection * uView * uModel * vec4(aPos,1.0);
}
