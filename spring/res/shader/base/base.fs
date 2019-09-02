#version 330 core

varying vec3 V_Vertex;

void main()
{
    vec3 color = V_Vertex + vec3(1.0);
    gl_FragColor = vec4(color / 2.0,1.0);
}