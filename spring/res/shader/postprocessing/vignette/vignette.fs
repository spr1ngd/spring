#version 330 core

out vec4 FragColor;

uniform sampler2D _MainTex;
uniform vec4 _MainColor;
uniform vec2 _Center;
uniform float _Intensity;
uniform float _Smoothness;
uniform float _Roundness;
uniform bool _Rounded;
uniform sampler2D _MaskTex;

in vec2 Texcoord;

void main()
{
    FragColor = texture(_MainTex,Texcoord);
}