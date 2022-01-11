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
out mat3 f_TBN;

// uniform mat4 uScale;
// uniform mat4 uRotate;
// uniform mat4 uTranslate;uModel
uniform mat4 uModel;

uniform mat4 uView;
uniform mat4 uProjection;

void main()
{
    //mat4 model =  uTranslate * uRotate * uScale;

    mat3 TBN = mat3(transpose(inverse(uModel)));
    //mat3 TBN =mat3(uModel);

    f_TBN = TBN;
    f_normal = TBN * aNormal;// mat3(model) * aNormal;
    f_texCoord = aTexCoord;
    
    f_worldPos = vec3(uModel * vec4(aPos, 1.0));

    //f_vertexColor = aColor;
    // gl_Position é uma das variaveis presentes no vertex shader
    // definirá a posição final do vértice
    // Deve ser um vec4 (X, Y, Z, W)
    gl_Position = uProjection * uView * uModel * vec4(aPos,1.0);
    
}
