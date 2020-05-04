#version 330 core

out vec4 FragColor;

uniform sampler2D Main_Texture;
uniform sampler2D AlphaTexture;

in vec2 TexCoord;

void main()
{
    vec2 uv = vec2(TexCoord.x,1.0 - TexCoord.y);
    vec4 texColor = texture(Main_Texture,uv);
    float a = texture(AlphaTexture,uv).r;
    if( a == 0.0 )
        discard;
    FragColor = vec4(texColor.rgb,a);
}