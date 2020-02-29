#version 330 core

layout (location = 0) out vec4 FragColor;
layout (location = 1) out vec4 BrightColor;

uniform sampler2D Main_Texture;

in vec2 Texcoord;

void main()
{
    vec4 color = texture(Main_Texture,Texcoord);
    float brightness = dot(color.rgb,vec3(0.2126,0.7152,0.0722));
    if( brightness > 1 )
        BrightColor = vec4(color.rgb,1.0);
    FragColor = color;
}