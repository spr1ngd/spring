
uniform samplerCube MAIN_CUBEMAP;

varying vec3 V_Vertex;

void main()
{
    // gl_FragColor = textureCube(MAIN_CUBEMAP,V_Vertex);
    gl_FragColor = vec4(1.0,1.0,0.0,1.0);
}