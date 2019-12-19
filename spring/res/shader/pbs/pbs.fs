#version 330 core

out vec4 FragColor;

#define LIGHT_POINT_COUNT 1
#define PI 3.14159

struct DirectionalLight
{
    vec3 position;
    vec4 color;
    float intensity;
};

uniform vec3 CameraPosition;
uniform DirectionalLight dirLights[LIGHT_POINT_COUNT];

uniform vec4 albedo; // 反射率
uniform float metal; // 金属度：用于菲涅尔方程式的
uniform float smoothness;// 光滑度：用于法线分布函数和几何函数，用来反映微平面的法线分布和微平面互相产生遮蔽的比率
uniform vec4 ao; // 环境光照(环境光遮蔽)

in vec4 WorldPos;
in vec3 Normal;
in vec2 Texcoord;

// 求解反射率方程
// calculate BRDF diffuse reflection part 漫反射部分
vec3 BRDFDiffuse(vec3 kd)
{
    return kd*albedo.rgb/PI;
}

// calculate D (normal distribution functoin) 法线分布函数
float NDFGGX(vec3 N,vec3 H,float smoothness)
{
    float NdotH = max(0.0,dot(N,H));
    float ss = pow(smoothness,2);
    float numerator = ss;
    float denominator = PI * pow( pow(NdotH,2) * (ss- 1) + 1 ,2 );
    return ss / (PI * pow( pow(NdotH,2) * (ss- 1) + 1 ,2 ));
}

// calculate G (geometry functoin) 几何函数 ： 包含几何遮蔽和几何阴影，以及直接光照和间接光照（IBL Image Based Lighting）

// direct lighting mode 直接光照
float smoothnessInDirectLighting( float smoothness )
{
    return pow(smoothness + 1,2) / 8;
}
// image based lighting mode 间接关照
float smoothnessInImageBasedLighting( float smoothness )
{
    return pow(smoothness,2) / 2;
}
// parameters : N(法线),V/L(视角方向或者入射方向),k(光滑度相对于直接关照和间接关照的重映射)
float GeometrySchlickGGX(vec3 N,vec3 VL,float k)
{
    float NDotVL = max(0.0,dot(N,VL));
    return NDotVL / (NDotVL * (1-k) + k);
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
// parameters : N(法线),V(视角方向) metal(金属度) surfaceColor(表面颜色)
vec3 FreshnelSchlich(vec3 N,vec3 V)
{
    vec3 F0 = vec3(0.04);//基础反射率
    F0 = mix(F0,albedo.rgb,metal);

    float NdotV = max(0.0,dot(N,V));
    return F0 + (1-F0)*pow(1-NdotV,5);
}

// calculate Balancing Coefficient BRDF配平系数
float BRDFCoefficient( vec3 N,vec3 L,vec3 V )
{
    float NdotL = max(0.0,dot(N,L));
    float NdotV = max(0.0,dot(N,V));
    return 4 * NdotL * NdotV + 0.001; // 防止为0
}

// calculate BRDF specular reflection part 镜面反射部分 (包含D,G,F三项公式,以及分母配平公式)
vec3 BRDFSpecular(vec3 N,vec3 H,vec3 V,vec3 L)
{
    float D = NDFGGX(N,H,smoothness);
    float kDirect = smoothnessInDirectLighting(smoothness);
    float kIBL = smoothnessInImageBasedLighting(smoothness);
    float G = GeometrySmith(N,V,L,kDirect);//基于直接光照的几何函数
    vec3 F = FreshnelSchlich(N,V);
    float coefficient = BRDFCoefficient(N,L,V);
    vec3 BRDF = D*G*F/coefficient;
    return BRDF;
}

// 积分过程，每个像素，基于上述所有运算步骤对每束入射光进行积分求解。
void main()
{
    vec3 N = normalize(Normal);
    vec3 V = normalize(CameraPosition - WorldPos.xyz);

    vec3 Lo = vec3(0.0);
    for( int i = 0 ; i < LIGHT_POINT_COUNT; i++ )
    {
        DirectionalLight light = dirLights[i];
        vec4 radiance = light.color * light.intensity; // 光照颜色可考虑衰减参数(平行光目前不考虑衰减)
        vec3 L = normalize(light.position - WorldPos.xyz);
        vec3 H = normalize(V + L);

        vec3 F = FreshnelSchlich(N,V);
        vec3 ks = F;
        vec3 kd = vec3(1.0) - ks;
        kd *= (1.0-metal); // 金属不具有漫反射特性

        vec3 diffuse = BRDFDiffuse(kd);
        vec3 specular = BRDFSpecular(N,H,V,L);
        float NdotL = max(0.0,dot(N,L));
        vec3 mix = diffuse + specular * radiance.rgb * NdotL;
        // vec3 mix = specular;
        Lo += mix;
    }

    vec3 ambient = vec3(0.03) * albedo.rgb * ao.rgb;
    vec3 color = Lo + ambient;
    color = color / (color + vec3(1.0));
    color = pow(color,vec3(1.0/2.2));
    FragColor = vec4(color,1.0);
}