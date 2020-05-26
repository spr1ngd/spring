#version 330 core

out vec4 FragColor;

uniform sampler2D Main_Texture;
in vec2 Texcoord;

float gaussian( float x, float sigma )
{
    return 0.39894228 * sigma * exp(-0.5 * x * x / (sigma * sigma));
}

float gaussian( float x,float y,float sigma)
{
    float sigmaP2 = sigma * sigma;
    return (0.15915494 / sigmaP2) * exp(-0.5 * (x*x + y*y) / sigmaP2);
}

void main()
{
    vec4 color = vec4(0.0,0.0,0.0,0.0);

    ivec2 ts2D = textureSize(Main_Texture,0);
    float texelX = 1.0 / ts2D.x;
    float texelY = 1.0 / ts2D.y;

    // 对输入进来的纹理进行高斯模糊
    const int sSize = 15;
    float kernel[sSize];
    int kSize = (sSize - 1) / 2;

    float sigma = 3.0;
    float Z = 0.0;
    for( int k = 0; k < kSize ; kSize++ )
    {
        kernel[kSize+k] = kernel[kSize-k] = gaussian(float(k),sigma);
    }

    for( int k = 0; k < sSize ; k++ )
    {
        Z += kernel[k];
    }

    for( int x = -kSize; x <= kSize ;x++)
    {
        for( int y = -kSize ; y <= kSize ; y++ )
        {
            float weight = kernel[kSize+x] * kernel[kSize +y];
            vec2 uv = Texcoord + vec2(texelX*x,texelY*y);
            color += texture(Main_Texture,uv) * weight;
        }
    }

    FragColor = color;
}