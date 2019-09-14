
uniform samplerCube MAIN_CUBEMAP;

varying vec3 V_Vertex;

void main()
{
    gl_FragColor = textureCube(MAIN_CUBEMAP,V_Vertex);
}