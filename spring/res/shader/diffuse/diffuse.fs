#version 330 core
out vec4 FragColor;

struct Light
{
    vec4 color;
    vec3 pos;
    vec4 direction;
    float intensity;
};

uniform sampler2D Main_Texture;
uniform vec4 Main_Color;
uniform vec4 AmbientColor;
uniform vec4 LightColor;
uniform vec3 LightPosition;
uniform vec3 LightDirection;
uniform float LightIntensity;
uniform Light light;

in vec3 V_WorldNormal;
in vec2 V_Texcoord;

void main()
{
    // ambient 
    vec4 ambient = AmbientColor;

    // diffuse 
    vec3 N = normalize(V_WorldNormal);
    // this only directional light in present.
    vec3 L = normalize(LightDirection.xyz);
    L = vec3(0.0,0.0,1.0);
    float NdotL = max(0.0,dot(N,L));
    vec4 diffuseColor = Main_Color * LightColor * NdotL * LightIntensity;

    // texture color
    vec4 tex = texture(Main_Texture,V_Texcoord);

    // FragColor = tex;
    FragColor = AmbientColor + diffuseColor;
}