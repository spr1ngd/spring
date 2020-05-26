#version 330 core

out vec4 FragColor;

#define LIGHT_POINT_COUNT 4
#define PI 3.14159265359

struct DirectionalLight
{
    vec3 position;
    vec4 color;
    float intensity;
};

uniform vec3 CameraPosition;
uniform DirectionalLight dirLights[LIGHT_POINT_COUNT];

uniform samplerCube irradianceMap;
uniform samplerCube prefilterMap;
uniform sampler2D prebrdfMap;
uniform vec4 albedo; // 反射率
uniform float metal; // 金属度：用于菲涅尔方程式的
uniform float roughness;// 粗糙度：用于法线分布函数和几何函数，用来反映微平面的法线分布和微平面互相产生遮蔽的比率
uniform vec4 ao; // 环境光照(环境光遮蔽)

uniform sampler2D albedoTex;
uniform sampler2D metallicTex;
uniform sampler2D normalTex;
uniform sampler2D heightTex;
uniform sampler2D occlusionTex;
uniform sampler2D detailMaskTex;

uniform sampler2D emissionTex;
uniform vec4 emissionColor;

in vec4 WorldPos;
in vec3 Normal;
in vec2 Texcoord;

// 求解反射率方程
// calculate BRDF diffuse reflection part 漫反射部分
vec3 BRDFDiffuse(vec3 kd,vec3 albedo)
{
    return kd*albedo/PI;
}

// calculate D (normal distribution functoin) 法线分布函数
float NDFGGX(vec3 N,vec3 H,float roughness)
{
    float NdotH = max(0.0,dot(N,H));
    float ss = pow(roughness,2);
    float numerator = ss * ss;
    float denominator = PI * pow( pow(NdotH,2) * (numerator- 1) + 1 ,2 );
    return numerator / denominator;
}

// calculate G (geometry functoin) 几何函数 ： 包含几何遮蔽和几何阴影，以及直接光照和间接光照（IBL Image Based Lighting）

// direct lighting mode 直接光照
float roughnessInDirectLighting( float roughness )
{
    float s1 = roughness + 1;
    float numerator = pow(s1,2);
    return numerator / 8;
}
// image based lighting mode 间接关照
float roughnessInImageBasedLighting( float roughness )
{
    return pow(roughness,2) / 2;
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

// calculate F (fresnel equation) 菲涅尔方程 : 引入金属度参数来表达金属工作流的概念
// parameters : N(法线),H(V和L的中间向量) metallic(金属度) surfaceColor(表面颜色)
vec3 FreshnelSchlick(vec3 N,vec3 H,float metallic,vec3 albedo)
{
    vec3 F0 = vec3(0.04);//基础反射率
    F0 = mix(F0,albedo,metallic);

    float NdotH = max(0.0,dot(N,H));
    return F0 + (1-F0)*pow(1-NdotH,5.0);
}

vec3 FreshnelSchlickRoughness( vec3 N,vec3 H ,float roughess ,float metallic,vec3 albedo)
{
    vec3 F0 = vec3(0.04);//基础反射率
    F0 = mix(F0,albedo,metallic);
    float NdotH = max(0.0,dot(N,H));
    return F0 + (max(vec3(1.0 -roughess),F0)-F0)*pow(1-NdotH,5.0);
}

// calculate Balancing Coefficient BRDF配平系数
float BRDFCoefficient( vec3 N,vec3 L,vec3 V )
{
    float NdotL = max(0.0,dot(N,L));
    float NdotV = max(0.0,dot(N,V));
    return 4 * NdotL * NdotV + 0.001; // 防止为0
}

// calculate BRDF specular reflection part 镜面反射部分 (包含D,G,F三项公式,以及分母配平公式)
vec3 BRDFSpecular(vec3 N,vec3 H,vec3 V,vec3 L,float metallic,vec3 albedo)
{
    float D = NDFGGX(N,H,roughness);
    float kDirect = roughnessInDirectLighting(roughness);
    float kIBL = roughnessInImageBasedLighting(roughness);
    float G = GeometrySmith(N,V,L,kDirect);//基于直接光照的几何函数
    vec3 F = FreshnelSchlick(N,H,metallic,albedo);
    float coefficient = BRDFCoefficient(N,L,V);
    vec3 BRDF = D*G*F/coefficient;
    return BRDF;
}

// transfer normal from tangent space to world space
vec3 TangentSpaceToWorldSpace(vec3 tangentNormal)
{
    vec3 Q1  = dFdx(WorldPos.xyz);
    vec3 Q2  = dFdy(WorldPos.xyz);
    vec2 st1 = dFdx(Texcoord);
    vec2 st2 = dFdy(Texcoord);

    vec3 N   = normalize(Normal);
    vec3 T  = normalize(Q1*st2.t - Q2*st1.t);
    vec3 B  = -normalize(cross(N, T));
    mat3 TBN = mat3(T, B, N);

    return normalize(TBN * tangentNormal);
}

// 积分过程，每个像素，基于上述所有运算步骤对每束入射光进行积分求解。
void main()
{
    vec3 albedoColor = albedo.rgb * texture(albedoTex,Texcoord).rgb; // 反射率   
    float metallic = metal * texture(metallicTex,Texcoord).r;// 金属度

    vec3 tangentNormal = texture(normalTex, Texcoord).rgb * 2.0 - 1.0;
    vec3 N = TangentSpaceToWorldSpace(tangentNormal);
    vec3 V = normalize(CameraPosition - WorldPos.xyz);
    vec3 R = reflect(-V,N);

    vec3 Lo = vec3(0.0);
    for( int i = 0 ; i < LIGHT_POINT_COUNT; i++ )
    {
        DirectionalLight light = dirLights[i];
        vec4 radiance = light.color * light.intensity; // 光照颜色可考虑衰减参数(平行光目前不考虑衰减)
        vec3 L = normalize(light.position - WorldPos.xyz);
        vec3 H = normalize(V + L);

        vec3 F = FreshnelSchlick(N,V,metallic,albedoColor);
        vec3 ks = F;
        vec3 kd = vec3(1.0) - ks;
        kd *= (1.0-metallic); // 金属不具有漫反射特性

        vec3 d = BRDFDiffuse(kd,albedoColor);
        vec3 s = BRDFSpecular(N,H,V,L,metallic,albedoColor);
        vec3 mix = (d + s) * radiance.rgb * max(0.0,dot(N,L));
        Lo += mix;
    }

    vec3 F = FreshnelSchlickRoughness(N,V,roughness,metallic,albedoColor);// 给菲涅尔反射加入粗糙度影响因子
    vec3 ks = F; 
    vec3 kd = vec3(1.0) - ks;
    kd *= (vec3(1.0)-metallic);

    // ibl diffuse part
    vec3 irradiance = texture(irradianceMap,N).rgb;
    vec3 diffuse = irradiance * albedoColor;

    // ibl specular part
    const float PREFILTER_MAX_LOD = 4.0;
    vec3 prefilterColor = textureLod(prefilterMap,R,roughness * PREFILTER_MAX_LOD).rgb;
    vec2 brdf = texture(prebrdfMap,vec2(max(0.0,dot(N,V)),roughness)).rg;
    vec3 brdfColor = F * brdf.r + vec3(brdf.g);
    vec3 specular = prefilterColor * brdfColor;
    vec3 ambient = ( kd * diffuse + specular) * ao.r; 
    vec3 color = Lo + ambient;

    // emission
    vec3 emission = texture(emissionTex,Texcoord).rgb * emissionColor.rgb; 
    color += emission;

    // color = color / (color + vec3(1.0)); // hdr
    // color = pow(color,vec3(0.45)); // gamma correct
    FragColor = vec4(color,1.0);
}