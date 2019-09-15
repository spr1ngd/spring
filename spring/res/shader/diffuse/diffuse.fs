
uniform sampler2D Main_Texture;

uniform vec4 Main_Color;
uniform vec4 AmbientColor;

uniform vec4 LightColor;
uniform vec3 LightPosition;
uniform vec3 LightDirection;
uniform float LightIntensity;

varying vec3 V_WorldNormal;
varying vec2 V_Texcoord;

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

    gl_FragColor = tex;
    // gl_FragColor = AmbientColor + diffuseColor + tex;
}