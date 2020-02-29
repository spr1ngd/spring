#version 330 core

out vec4 FragColor;

uniform sampler2D Main_Texture;
in vec2 Texcoord;
vec4 OutlineColor = vec4(0.71,0.95,0.0,1.0);

void main()
{

    float offset = 1.5 / textureSize(Main_Texture,0).x;
    vec2 offsets[9] = vec2[]
    (
        vec2(-offset,offset), vec2(0,offset),  vec2(offset,offset),
        vec2(-offset,0),      vec2(0,0),       vec2(offset,0),
        vec2(-offset,-offset),vec2(0,-offset), vec2(offset,-offset)
    ); 
    vec3 color = vec3(0.0);

    float kernel[9] = float[]
    (
        1,1,1,
        1,-7,1,
        1,1,1
    );
    for( int i = 0 ; i < 9 ; i++ )
    {
        color += texture(Main_Texture,Texcoord.st + offsets[i]).rgb * kernel[i];
    }

    // float sobelX[9] = float[]
    // (
    //     1,0,-1,
    //     2,0,-2,
    //     1,0,-1
    // );

    // float sobelY[9] = float[]
    // (
    //     1, 2, 1,
    //     0, 0, 0,
    //     -1,-2,-1
    // );

    // for( int i = 0 ; i < 9 ; i++ )
    // {
    //     color += texture(Main_Texture,Texcoord.st + offsets[i]).rgb * sobelX[i];
    //     color += texture(Main_Texture,Texcoord.st + offsets[i]).rgb * sobelY[i];
    // }
    // color += texture(Main_Texture,Texcoord).rgb;

    // float average = (color.r + color.g + color.b) / 3.0;
    // if( average > 0.8 )
    //     color = OutlineColor.rgb + texture(Main_Texture,Texcoord).rgb;
    // else
    //     color = texture(Main_Texture,Texcoord).rgb;
    FragColor = vec4(color,1.0);
}