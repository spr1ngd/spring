
uniform sampler2D Main_Texture;

varying vec2 V_Texcoord;

void main()
{
    gl_FragColor = texture2D(Main_Texture,V_Texcoord);
}