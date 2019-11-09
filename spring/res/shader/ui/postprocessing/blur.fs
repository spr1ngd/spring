#version 330 core

out vec4 FragColor;

uniform sampler2D Main_Texture;
in vec2 Texcoord;
in vec4 Color;

void main()
{	
    float dv = 1.5/textureSize(Main_Texture,0).x;
	vec4 color = vec4(0.0);
	int seg = 5;
	float f = 0.0f;
	float tot = 0.0f;
	for( int i = -seg; i <= seg; ++i)
	{
		for( int j = -seg; j <= seg; ++j)
		{
			f = (1.1 - sqrt(i*i + j*j)/8.0);
			f *= f;
			tot += f;
			color += texture( Main_Texture, vec2(Texcoord.x + j * dv, Texcoord.y + i * dv) ).rgba * f;
		}
	}
	color /= tot;
	FragColor = color;
}