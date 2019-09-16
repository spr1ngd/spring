#version 330 core
out vec4 FragColor;

struct Light
{
    vec4 color;
    vec3 position;
    vec4 direction;
    float intensity;
    float range;

    float cutoff;
    float outerCutoff;
    
    float constant;
    float linear;
    float quadratic;
};

uniform sampler2D Main_Texture;
uniform vec4 Main_Color;
uniform vec4 AmbientColor;

uniform vec4 Specular_Color;
uniform float Specular_Attenuation;
uniform float Specular_Intensity;

uniform vec3 CameraPosition;
uniform Light light;

in vec4 WorldPos;
in vec3 WorldNormal;
in vec2 Texcoord; 
void main()
{
    // ambient 
    vec4 ambient = AmbientColor;

    // diffuse 
    vec3 N = normalize(WorldNormal);
    vec3 L = vec3(0.0);

    //specular
    vec3 reflectDir = vec3(0.0);
    vec3 cameraDir = normalize(WorldPos.xyz - CameraPosition);
    float relfectIntensity = 0.0f;

    float attenuation = 0.0;

    if( light.direction.w == 0.0 ) // directional light
    { 
        L = normalize(light.position.xyz);
        attenuation = 1.0;
    }
    else if( light.direction.w == 1.0 )
    {
        if (light.cutoff == 0.0) // point light
        {
            float distance = length(WorldPos.xyz - light.position);
            L = normalize(light.position - WorldPos.xyz);
            if( distance < light.range )
            {
                attenuation = 1.0 / (light.constant + light.linear * distance + light.quadratic * (distance*distance));
            }
        }
        else// spot light
        {
            float distance = length(WorldPos.xyz-light.position);
            L = normalize(light.position-WorldPos.xyz);
            vec3 lightDir = normalize(light.direction.xyz);
            float theta = max(0.0,dot(-L,lightDir));
            float maxDistance = light.range / theta;
            if( distance < maxDistance)
            { 
                if( theta > light.outerCutoff)
                {
                    float spotIntensity = clamp( (theta - light.outerCutoff)/(light.cutoff-light.outerCutoff) ,0.0,1.0 );
                    attenuation = 1.0 / (light.constant + light.linear * distance + light.quadratic * (distance*distance)) * spotIntensity;
                }
            }
        }
    }

    vec4 diffuse = Main_Color * light.color * max(0.0,dot(N,L)) * light.intensity * attenuation;

    // specular... 
    
    reflectDir = reflect(-L,N);
    relfectIntensity = max(0.0,dot(reflectDir,-cameraDir)); 
    vec4 specular = Specular_Color * pow(relfectIntensity,Specular_Attenuation) * Specular_Intensity;

    // FragColor = tex;
    FragColor = ambient + diffuse + specular;
}