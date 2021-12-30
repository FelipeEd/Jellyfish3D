#version 330 core

// Location define a posição do atributo no VAO
layout (location = 0) in vec3 aPos;
layout (location = 1) in vec4 aColor;

out vec4 vertexColor;
uniform mat4 uTransform;
uniform mat4 uView;
uniform mat4 uProjection;


void main()
{
    // gl_Position é uma das variaveis presentes no vertex shader
    // definirá a posição final do vértice
    // Deve ser um vec4 (X, Y, Z, W)
    vertexColor = aColor;
    gl_Position =  uProjection * uView * uTransform * vec4(aPos,1.0);
    
}
