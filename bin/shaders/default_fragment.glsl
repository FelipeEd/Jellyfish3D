#version 330 core

out vec4 FragColor;
in vec4 vertexColor;
// uniforms são variáveis alteradas no código OpenGL
uniform vec4 uColor;

void main()
{
    FragColor = vertexColor ; //RGBA
} 