#version 330 core

out vec4 FragColor;

const float BlurSize = 1.0;

uniform sampler2D Main_Texture;
uniform vec4 _ScreenParams;
in vec2 Texcoord;

// void main()
// {
//     float depth = texture(Main_Texture,Texcoord).r;
//     FragColor = vec4(vec3(depth),1.0);
// }

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
    float depth = 0.0;

    ivec2 ts2D = textureSize(Main_Texture,0); 

    // 对输入进来的纹理进行高斯模糊
    const int sSize = 5;
    float kernel[sSize];
    int kSize = (sSize - 1) / 2;

    float sigma = 3.0;
    float Z = 0.0;
    for( int k = 0; k <= kSize ; k++ )
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
            vec2 uv = Texcoord + vec2(_ScreenParams.x * x,_ScreenParams.y * y) * BlurSize;
            depth += texture(Main_Texture,uv).r * weight;
        }
    }
    depth /= Z * Z;
    FragColor = vec4(depth,depth,depth,1.0);
}