#version 330 core
out vec4 FragColor;
uniform samplerCube Main_Cubemap;
uniform float time;

in vec3 V_Vertex;

void main()
{
    float lod = 0.5 * sin(time * 2.0) + 0.5;
    vec3 color = textureLod(Main_Cubemap,V_Vertex,lod).rgb;
    FragColor = vec4(color,1.0);
}