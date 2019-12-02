#version 330 core

out vec4 FragColor;

uniform vec4 Main_Color;
uniform sampler2D Main_Texture;

in vec2 Texcoord;

void main()
{
    vec4 texColor = texture(Main_Texture,Texcoord);
    // FragColor = texColor;
    float brightness = dot(texColor.rgb, vec3(0.2126, 0.7152, 0.0722));
    if( brightness > 1.0 )
        FragColor = vec4(1.0,1.0,0.0,1.0);
    else
        FragColor = vec4(1.0,0.0,0.0,1.0);
}