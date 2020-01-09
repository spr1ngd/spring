#version 330 core

#define PI 3.1415926

out vec4 FragColor;
in vec2 Texcoord;

float RadicalInverse_VDC(uint bits);
vec2 Hammersley(uint i,uint N);
vec3 ImportanceSampleGGX(vec2 Xi,vec3 N,float roughness);
float GeometrySchlickGGX(vec3 N,vec3 VL,float k);
float GeometrySmith( vec3 N,vec3 V,vec3 L,float k);

void main()
{
    float NdotV = Texcoord.x;
    float roughness = Texcoord.y;

    vec3 V = vec3(0.0);
    V.x = sqrt(1.0 - NdotV*NdotV); // sin
    V.y = 0.0;
    V.z = NdotV;    // cos

    float X = 0.0;
    float Y = 0.0;
    vec3 N = vec3(0.0,0.0,1.0);  

    // TODO: finished precalculate brdf.
    uint SAMPLE_COUNT = 1024u;
    // 预计算brdf积分结果
    for( uint i = 0u ;i < SAMPLE_COUNT ;i++ )
    {
        // 获取低差异序列
        vec2 Xi = Hammersley(i,SAMPLE_COUNT);
        // 重要性采样获取中间向量
        vec3 H = ImportanceSampleGGX(Xi,N,roughness);
        vec3 L = normalize(2.0 * dot(V,H) *H - V);

        float kIBL = roughness * roughness / 2.0;

        float NdotL = max(0.0,dot(N,L));
        float VdotH = max(0.0,dot(V,H));
        float NdotH = max(0.0,dot(N,H));
        if( NdotL > 0.0)
        {
            float G = GeometrySmith(N,V,L,kIBL);
            float G_vis =(G * VdotH) / (NdotH * NdotV);
            float F = pow(1.0 - VdotH,5.0);

            X += (1.0 - F) * G_vis;
            Y += F * G_vis;
        }
    }

    X /= float(SAMPLE_COUNT);
    Y /= float(SAMPLE_COUNT);
    FragColor = vec4(X,Y,0.0,1.0);
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

// 重要性采样
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

// parameters : N(法线),V/L(视角方向或者入射方向),k(光滑度相对于直接关照和间接关照的重映射)
float GeometrySchlickGGX(vec3 N,vec3 VL,float k)
{
    float NDotVL = max(0.0,dot(N,VL));
    float denominator = NDotVL * (1-k) + k;
    return NDotVL / denominator;
}

// Smith法纳入几何遮蔽（视角方向）和几何阴影（光入射方向）
// parameters : 
float GeometrySmith( vec3 N,vec3 V,vec3 L,float k)
{
    float geometryObstruction = GeometrySchlickGGX(N,V,k);  // 几何遮蔽
    float geometryShadowing = GeometrySchlickGGX(N,L,k);    // 几何阴影
    return geometryObstruction * geometryShadowing;
}