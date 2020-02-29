#version 330 core

out vec4 FragColor;

uniform sampler2D Main_Texture; // this is a hrd framebuffer
uniform float exposure;

in vec2 Texcoord;

void main()
{
    const float gamma = 2.2;
    vec3 hdr = texture(Main_Texture,Texcoord).rgb;
    // tone mapping
    vec3 mapped = vec3(1.0) - exp(-hdr * exposure);
    // gamma correction
    vec3 color = pow(mapped,vec3(1.0 / gamma));
    FragColor = vec4(color,1.0);
}