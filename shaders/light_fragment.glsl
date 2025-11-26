#version 330 core

out vec4 FragColor;
in vec3 f_vertexColor;
in vec3 f_normal;
in vec2 f_texCoord;

uniform vec4 uColor;


void main()
{
    
    FragColor = uColor;//FragColor = vec4(pow(uColor.rgb , vec3(2.2)),1.0);
} 