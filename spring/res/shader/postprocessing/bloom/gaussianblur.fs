#version 330 core

out vec4 FragColor;

uniform sampler2D Main_Texture;
uniform bool hSample; // sample in horizontal direction

in vec2 Texcoord;

void main()
{
    int kernelSize = 5;
    float weight[5] = float[](0.227027, 0.1945946, 0.1216216, 0.054054, 0.016216);

    vec2 textureOffset = 1.0 / textureSize(Main_Texture,0);
    vec3 result = texture(Main_Texture,Texcoord).rgb * weight[0];

    if( hSample )
    {
        for( int i = 1; i < kernelSize;i++ )
        {
            // left
            result += texture(Main_Texture,Texcoord + vec2(i * textureOffset.x,0)).rgb * weight[i];
            // right
            result += texture(Main_Texture,Texcoord + vec2(-i * textureOffset.x,0)).rgb * weight[i];
        }
    }
    else
    {
        for( int i = 1; i < kernelSize; i++)
        {
            // top
            result += texture(Main_Texture,Texcoord + vec2(0,i * textureOffset.y)).rgb * weight[i];
            // bottom
            result += texture(Main_Texture,Texcoord + vec2(0,-i * textureOffset.y)).rgb * weight[i];
        }
    }
    FragColor = vec4(result,1.0);
}