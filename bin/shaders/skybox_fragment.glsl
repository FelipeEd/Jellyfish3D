#version 330 core
out vec4 FragColor;

in vec3 f_texCoord;

uniform samplerCube uTexSkybox;

void main()
{    
    FragColor = texture(uTexSkybox, f_texCoord);
}