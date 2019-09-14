
attribute vec3 vertex;

uniform mat4 M;
uniform mat4 V;
uniform mat4 P;

varying vec3 V_Vertex;

void main()
{
    V_Vertex = vertex;
    gl_Position = P * V * M * vec4(vertex,1.0);
}