#version 330 core

out vec4 FragColor;

uniform sampler2D Main_Texture;
uniform float gamma;
in vec2 Texcoord;

vec3 linearToGamma( vec3 lColor)
{
    float r = pow(lColor.r,0.45);
    float g = pow(lColor.g,0.45);
    float b = pow(lColor.b,0.45);
    return vec3(r,g,b);
}

vec3 gammaToLinear( vec3 gColor)
{
    float r = pow(gColor.r,2.2);
    float g = pow(gColor.g,2.2);
    float b = pow(gColor.b,2.2);
    return vec3(r,g,b);
} 

void main()
{
    vec3 color = texture(Main_Texture,Texcoord).rgb;
    color = color / (color + vec3(1.0));
    color = pow(color,vec3(1.0/2.2));
    FragColor = vec4(color,1.0);
}