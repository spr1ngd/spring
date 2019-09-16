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
            
        }
        else// spot light
        {
            attenuation = 0.0;
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

    vec4 diffuseColor = Main_Color * light.color * max(0.0,dot(N,L)) * light.intensity * attenuation;

    // specular...

    // FragColor = tex;
    FragColor = AmbientColor + diffuseColor;
}