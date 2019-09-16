#version 330 core
out vec4 FragColor;
uniform samplerCube Main_Cubemap;

in vec3 V_Vertex;

void main()
{
    FragColor = texture(Main_Cubemap,V_Vertex);
}