#version 330 core

out vec4 FragColor;

in vec2 Texcoord;

uniform vec3 WorldSpaceCameraPos;
uniform int meshCount = 5;

float around(float x,float y)
{
    float r = floor(x/y);
    float remainder = mod(x,y);
    if( remainder >= y * 0.5 )
        r += 1;
    return r;
}

const float lineWidthFactor = 0.01 / 1.5;

void main()
{
    float distance = sqrt(
        WorldSpaceCameraPos.x * WorldSpaceCameraPos.x + 
        WorldSpaceCameraPos.y * WorldSpaceCameraPos.y +
        WorldSpaceCameraPos.z * WorldSpaceCameraPos.z);

    float lineWidth = lineWidthFactor * distance;

    vec4 color = vec4(0.0,0.0,0.0,0.0);
    float offset = 1.0 / meshCount;
    float halfLineWidth = lineWidth * 0.5;
    float xr = around(Texcoord.x,offset);
    float xmin = clamp(offset * xr - halfLineWidth,0.0,1.0);
    float xmax = clamp(offset * xr + halfLineWidth,0.0,1.0);

    float yr = around(Texcoord.y,offset);
    float ymin = clamp(offset * yr - halfLineWidth,0.0,1.0);
    float ymax = clamp(offset * yr + halfLineWidth,0.0,1.0);

    if( Texcoord.x > xmin && Texcoord.x <= xmax)
        color = vec4(1.0,1.0,1.0,1.0);
    if( Texcoord.y > ymin && Texcoord.y <= ymax )
        color = vec4(1.0,1.0,1.0,1.0);
    FragColor = color;
}