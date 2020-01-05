#version 330 core

out vec4 FragColor;
uniform samplerCube environmentCubemap;
const float PI = 3.14159265359;
const float SAMPLE_DELTA = 0.025;
in vec3 WorldPos;

void main()
{
    vec3 N = normalize(WorldPos);
    vec3 up = vec3(0.0,1.0,0.0);
    vec3 right = cross(up,N);
    up = cross(N,right);

    vec3 irradiance = vec3(0.0);
    float samples = 0;

    for( float phi = 0; phi < 2*PI ; phi+= SAMPLE_DELTA )
    {
        for( float theta = 0.0 ; theta < 0.5 * PI ; theta += SAMPLE_DELTA)
        {
            vec3 spherePos = vec3( cos(phi) * cos(theta),sin(phi)*cos(theta),sin(theta));
            vec3 wPos = spherePos.x * right + spherePos.y * up + spherePos.z * N;
            irradiance += texture(environmentCubemap,wPos).rgb * cos(theta) * sin(theta);
            samples++;   
        }
    }
    irradiance = PI * irradiance * (1.0 / samples);
    FragColor = vec4(irradiance,1.0);
}