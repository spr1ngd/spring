#version 330 core
#define PI 3.1415926

out vec4 FragColor;

uniform samplerCube environmentCubemap;
uniform float roughness;

in vec3 WorldPos;
in vec3 Normal;
in vec2 Texcoord;

float RadicalInverse_VDC(uint bits);
vec2 Hammersley(uint i,uint N);
vec3 ImportanceSampleGGX(vec2 Xi,vec3 N,float roughness);

void main()
{
    uint SAMPLE_COUNT = 1024u;
    vec3 N = normalize(WorldPos);
    vec3 R = N;
    vec3 V = R;

    float totalWeight = 0.0;
    vec3 prefilterColor = vec3(0.0);
    for(uint i = 0u; i < SAMPLE_COUNT;i++ )
    {
        // 获取低差异序列
        vec2 Xi = Hammersley(i,SAMPLE_COUNT);
        // 重要性采样
        vec3 H = ImportanceSampleGGX(Xi,N,roughness);
        vec3 L = normalize(2.0 * dot(V,H) *H - V);

        float NdotL = max(0.0,dot(N,L));
        if( NdotL > 0.0 )
        {
            prefilterColor += texture(environmentCubemap,L).rgb * NdotL;
            totalWeight += NdotL;
        }
    }
    prefilterColor = prefilterColor / totalWeight;
    FragColor = vec4(prefilterColor,1.0);
}

float RadicalInverse_VDC( uint bits )
{
    bits = (bits << 16u) | (bits >> 16u);
    bits = ((bits & 0x55555555u) << 1u) | ((bits & 0xAAAAAAAAu) >> 1u);
    bits = ((bits & 0x33333333u) << 2u) | ((bits & 0xCCCCCCCCu) >> 2u);
    bits = ((bits & 0x0F0F0F0Fu) << 4u) | ((bits & 0xF0F0F0F0u) >> 4u);
    bits = ((bits & 0x00FF00FFu) << 8u) | ((bits & 0xFF00FF00u) >> 8u);
    return float(bits) * 2.3283064365386963e-10; // / 0x100000000
}
// 从样本大小为N的样本集中获取低差异样本i
vec2 Hammersley(uint i,uint N)
{
    return vec2(float(i)/float(N),RadicalInverse_VDC(i));
}

vec3 ImportanceSampleGGX( vec2 Xi,vec3 N,float roughness )
{
    float a = roughness*roughness;

    float phi = 2.0 * PI * Xi.x;
    float cosTheta = sqrt((1.0 - Xi.y) / (1.0 + (a*a - 1.0) * Xi.y));
    float sinTheta = sqrt(1.0 - cosTheta*cosTheta);

    // from spherical coordinates to cartesian coordinates
    vec3 H;
    H.x = cos(phi) * sinTheta;
    H.y = sin(phi) * sinTheta;
    H.z = cosTheta;

    // from tangent-space vector to world-space sample vector
    vec3 up        = abs(N.z) < 0.999 ? vec3(0.0, 0.0, 1.0) : vec3(1.0, 0.0, 0.0);
    vec3 tangent   = normalize(cross(up, N));
    vec3 bitangent = cross(N, tangent);

    vec3 sampleVec = tangent * H.x + bitangent * H.y + N * H.z;
    return normalize(sampleVec);
}