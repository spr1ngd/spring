#version 330 core

out vec4 FragColor;

in vec4 WorldPos;
in vec2 Texcoord;

uniform vec3 WorldSpaceCameraPos;

float around(float x,float y)
{
    float r = floor(x/y);
    float remainder = mod(x,y);
    if( remainder >= y * 0.5 )
        r += 1;
    return r;
}

const int meshCount = 5;
const float LineWidthMax = 0.00005;
const float lineWidthMin = 0.000025;
const float lineWidthFactor = 0.00001 / 1;

vec4 drawMesh( float count , vec4 maincolor ,float lineWidth)
{
    vec4 color = vec4(0.0,0.0,0.0,0.0);

    float offset = 1.0 / count;
    float halfLineWidth = lineWidth * 0.5;
    float xr = around(Texcoord.x,offset);
    float xmin = clamp(offset * xr - halfLineWidth,0.0,1.0);
    float xmax = clamp(offset * xr + halfLineWidth,0.0,1.0);

    float yr = around(Texcoord.y,offset);
    float ymin = clamp(offset * yr - halfLineWidth,0.0,1.0);
    float ymax = clamp(offset * yr + halfLineWidth,0.0,1.0);

    if( Texcoord.x > xmin && Texcoord.x <= xmax)
        color = maincolor;
    if( Texcoord.y > ymin && Texcoord.y <= ymax )
        color = maincolor;

    return color;
}

void main()
{
    vec3 offset = WorldSpaceCameraPos - WorldPos.xyz;
    float camera2Frag = sqrt(offset.x * offset.x + offset.y * offset.y + offset.z * offset.z);
    float distance = abs(WorldSpaceCameraPos.y);
    // TODO: distance 取相机与水平面的交点的距离
    float lineWidth = lineWidthFactor * distance;
    lineWidth = clamp(lineWidth,lineWidthMin,LineWidthMax);
    vec4 color = vec4(0.0,0.0,0.0,0.0);
    
    int MAX = 0;
    if( distance > 0 && distance <= 16 )
    {
        MAX = int(ceil(log2(distance)));
    }
    else if( distance > 16 && distance <= 64)
    {
        MAX = int(ceil(log2(log2(distance))));
    }
    else
    {
        MAX = int(ceil(log2(log2(log2(distance)))));
    }
    int MIN = clamp(MAX-1,1,MAX);

    color += drawMesh( pow(meshCount,MIN) , vec4(1.0,1.0,1.0, 0.3) , lineWidthFactor * distance );
    color += drawMesh( pow(meshCount,MAX) , vec4(1.0,1.0,1.0, 0.15) , lineWidthFactor * distance );
    FragColor = color;
}