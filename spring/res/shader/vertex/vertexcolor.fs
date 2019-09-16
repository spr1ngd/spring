#version 330 core
out vec4 FragColor;
in vec4 V_VertexColor;

void main()
{
    FragColor = V_VertexColor;    
}