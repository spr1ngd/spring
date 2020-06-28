#version 330 core
// #include springcg.cginc // TODO: implement include for spring engine shader compiler.

out vec4 FragColor;

uniform sampler2D Main_Texture;
uniform vec4 _MainColor;
uniform float _Mode;
uniform vec2 _Center;
uniform float _Intensity;
uniform float _Smoothness;
uniform sampler2D _MaskTex;

in vec2 Texcoord;

void main()
{
    if( _Mode == 0 )
    {
        vec2 remapUV = Texcoord * 2.0 - 1.0;
        float sdf = distance(remapUV,_Center);
        sdf -= _Intensity;
        sdf = pow(sdf,1/_Smoothness);
        sdf = clamp(sdf,0.0,1.0);
        vec4 mainColor = texture(Main_Texture,Texcoord);
        vec3 color = mainColor.rgb * clamp(1.0-sdf,0.0,1.0) + _MainColor.rgb * clamp(sdf,0.0,1.0);
        FragColor = vec4(color,1.0);
    }
    else
    {
        float sdf = texture(_MaskTex,Texcoord).r;
        vec4 mainColor = texture(Main_Texture,Texcoord);
        vec3 color = mainColor.rgb * (1.0-sdf) + _MainColor.rgb * sdf;
        FragColor = vec4(color,1.0);
    }
}