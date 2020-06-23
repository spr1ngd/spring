#version 330 core

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

float sdfSllipse( float a,float b, vec2 uv,vec2 center)
{
    float x = uv.x - center.x;
    float y = uv.y - center.y;
    float aa = a * a;
    float bb = b * b;
    float xx = x * x;
    float yy = y * y;
    return (xx * bb + yy * aa - aa * bb ) / (aa * bb);
}

void main()
{
    float a = 0.5;
    float b = 0.5;
    float whRate = _ScreenParams.z / _ScreenParams.w;
    if( _Rounded == true )
        a = b / whRate;
    float l = sdfSllipse(a,b,Texcoord,_Center);
    l = 1.0 - distance(Texcoord,_Center);
    vec4 mainColor = texture(Main_Texture,Texcoord);
    vec3 color = mainColor.rgb * l + _MainColor.rgb * (1.0 - l);
    FragColor = vec4(color,1.0);
}