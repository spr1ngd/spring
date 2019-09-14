
uniform samplerCube Main_Cubemap;

varying vec3 V_Vertex;

void main()
{
    gl_FragColor = textureCube(Main_Cubemap,V_Vertex);
}