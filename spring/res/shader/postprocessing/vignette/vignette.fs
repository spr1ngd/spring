#version 330 core
// #include springcg.cginc // TODO: implement include for spring engine shader compiler.

out vec4 FragColor;

uniform sampler2D Main_Texture;
uniform vec4 _MainColor;
uniform vec2 _Center;
uniform float _Intensity;
uniform float _Smoothness;
uniform float _Roundness;
uniform bool _Rounded;
uniform sampler2D _MaskTex;
uniform vec4 _ScreenParams;

in vec2 Texcoord;

void main()
{
    float a = 0.5;
    float b = 0.5;
    float whRate = _ScreenParams.z / _ScreenParams.w;
    if( _Rounded == true )
        a = b / whRate; 
    float sdf = distance(Texcoord,_Center);
    sdf += (_Intensity-0.75);
    sdf /= (_Smoothness + 0.000001);
    sdf = clamp(sdf,0.0,1.0);
    vec4 mainColor = texture(Main_Texture,Texcoord);
    vec3 color = mainColor.rgb * clamp(1.0-sdf,0.0,1.0) + _MainColor.rgb * clamp(sdf,0.0,1.0);
    FragColor = vec4(color,1.0);
}