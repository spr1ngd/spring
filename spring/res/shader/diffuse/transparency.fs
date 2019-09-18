#version 330 core
out vec4 FragColor;

#define LIGHT_DIRECTIONAL_COUNT 1
#define LIGHT_POINT_COUNT 4
#define LIGHT_SPOT_COUNT 1

struct TextureData
{
    sampler2D texture;
    vec2 tilling;
    vec2 offset;
};

struct DirectionalLight
{
    vec4 color;
    vec3 position;
    float intensity;
};

struct SpotLight
{
    vec4 color;
    vec3 position;
    vec3 direction;
    float intensity;
    float range;

    float cutoff;
    float outerCutoff;
    
    float constant;
    float linear;
    float quadratic;
};

struct PointLight
{
    vec4 color;
    vec3 position;
    float intensity;
    float range;

    float constant;
    float linear;
    float quadratic;
}; 

uniform vec4 Main_Color;
uniform vec4 AmbientColor;
uniform vec4 Specular_Color;
uniform float Specular_Attenuation;
uniform float Specular_Intensity;

uniform vec3 CameraPosition; 

uniform TextureData MainTextureData;
uniform DirectionalLight dirLights[LIGHT_DIRECTIONAL_COUNT];
uniform SpotLight spotLights[LIGHT_SPOT_COUNT];
uniform PointLight pointLights[LIGHT_POINT_COUNT];

in vec4 WorldPos;
in vec3 WorldNormal;
in vec2 Texcoord; 

vec4 calcDirectionalLight(DirectionalLight lightData)
{
    vec4 OUT = vec4(0.0);

    // diffuse 
    vec3 N = normalize(WorldNormal);
    vec3 L = vec3(0.0);

    //specular
    vec3 reflectDir = vec3(0.0);
    vec3 cameraDir = normalize(WorldPos.xyz - CameraPosition);
    float relfectIntensity = 0.0f;

    float attenuation = 0.0;

    L = normalize(lightData.position.xyz);
    attenuation = 1.0;

    vec4 diffuse = Main_Color * lightData.color * max(0.0,dot(N,L)) * lightData.intensity * attenuation;

    // specular... 
    
    reflectDir = reflect(-L,N);
    relfectIntensity = max(0.0,dot(reflectDir,-cameraDir)); 
    vec4 specular = Specular_Color * pow(relfectIntensity,Specular_Attenuation) * Specular_Intensity;

    OUT = diffuse + specular;
    return OUT;
}

vec4 calcSpotLight( SpotLight lightData )
{
    vec4 OUT = vec4(0.0);

    // diffuse 
    vec3 N = normalize(WorldNormal);
    vec3 L = vec3(0.0);

    //specular
    vec3 reflectDir = vec3(0.0);
    vec3 cameraDir = normalize(WorldPos.xyz - CameraPosition);
    float relfectIntensity = 0.0f;

    float attenuation = 0.0;

    float distance = length(WorldPos.xyz-lightData.position);
    L = normalize(lightData.position-WorldPos.xyz);
    vec3 lightDir = normalize(lightData.direction.xyz);
    float theta = max(0.0,dot(-L,lightDir));
    float maxDistance = lightData.range / theta;
    if( distance < maxDistance)
    {  
        if( theta > lightData.outerCutoff)
        { 
            float spotIntensity = clamp( (theta - lightData.outerCutoff)/(lightData.cutoff-lightData.outerCutoff) ,0.0,1.0 );
            attenuation = 1.0 / (lightData.constant + lightData.linear * distance + lightData.quadratic * (distance*distance)) * spotIntensity;
        }
    }

    vec4 diffuse = Main_Color * lightData.color * max(0.0,dot(N,L)) * lightData.intensity * attenuation;

    // specular...     
    reflectDir = reflect(-L,N);
    relfectIntensity = max(0.0,dot(reflectDir,-cameraDir)); 
    vec4 specular = Specular_Color * pow(relfectIntensity,Specular_Attenuation) * Specular_Intensity;

    OUT = diffuse + specular;
    return OUT;
}

vec4 calcPointLight( PointLight lightData )
{
    vec4 OUT = vec4(0.0);

    // diffuse 
    vec3 N = normalize(WorldNormal);
    vec3 L = vec3(0.0);

    //specular
    vec3 reflectDir = vec3(0.0);
    vec3 cameraDir = normalize(WorldPos.xyz - CameraPosition);
    float relfectIntensity = 0.0f;

    float attenuation = 0.0;

    float distance = length(WorldPos.xyz - lightData.position);
    L = normalize(lightData.position - WorldPos.xyz);
    if( distance < lightData.range )
    {
        attenuation = 1.0 / (lightData.constant + lightData.linear * distance + lightData.quadratic * (distance*distance));
    }

    vec4 diffuse = Main_Color * lightData.color * max(0.0,dot(N,L)) * lightData.intensity * attenuation;

    // specular... 
    
    reflectDir = reflect(-L,N);
    relfectIntensity = max(0.0,dot(reflectDir,-cameraDir)); 
    vec4 specular = Specular_Color * pow(relfectIntensity,Specular_Attenuation) * Specular_Intensity;

    // FragColor = tex;
    OUT = diffuse + specular;

    return OUT;
} 

float calcMod( float a,float b )
{
    return a - b * floor(a / b);
}

void main()
{
    // ambient 
    vec4 ambient = AmbientColor;
    
    for( int i = 0 ; i < LIGHT_DIRECTIONAL_COUNT;i++ )
    {
        FragColor += calcDirectionalLight(dirLights[i]);
    }

    for( int i = 0 ; i < LIGHT_SPOT_COUNT;i++ )
    {
        FragColor += calcSpotLight(spotLights[i]);
    }

    for( int i = 0 ; i < LIGHT_POINT_COUNT;i++ )
    {
        FragColor += calcPointLight(pointLights[i]);
    } 

    vec2 offsetUV = Texcoord + MainTextureData.offset;
    vec2 texcoord = vec2( calcMod(offsetUV.x * MainTextureData.tilling.x,1.0),calcMod(offsetUV.y * MainTextureData.tilling.y ,1.0) ) ;
    vec4 texColor = texture(MainTextureData.texture,texcoord);

    FragColor += ambient;
    FragColor += texColor;
    FragColor = vec4(FragColor.rgb,Main_Color.a);
}