#version 330 core

layout (points) in;
layout (line_strip, max_vertices = 2) out;

in gl_Vertex
{
    vec4  gl_Position;
    float gl_PointSize;
    float gl_ClipDistance[];
} gl_in[];

const int meshCount = 5;
const vec3 origin = vec3(-0.5,-0.5,0.0);

void main()
{
    // float per = 1.0 / meshCount;
// 
    // for( int i = 0 ; i <= meshCount; i++ )
    // {
    //     gl_Position = gl_in[0].gl_Position + vec4( i * per ,0.0,0.0,0.0 );
    //     EmitVertex();
    //     gl_Position = gl_in[0].gl_Position + vec4( i * per ,1.0,0.0,0.0 );
    //     EmitVertex();
    //     EndPrimitive();
    // }
    // for( int i = 0; i <= meshCount;i++ )
    // {
    //     gl_Position = gl_in[0].gl_Position + vec4(0.0, i * per,0.0,0.0 );
    //     EmitVertex();
    //     gl_Position = gl_in[0].gl_Position + vec4(1.0, i * per,0.0,0.0 );
    //     EmitVertex();
    //     
    //     EndPrimitive();
    // }
    gl_Position = gl_in[0].gl_Position + vec4(-0.1, 0.0, 0.0, 0.0); 
    EmitVertex();

    gl_Position = gl_in[0].gl_Position + vec4( 0.1, 0.0, 0.0, 0.0);
    EmitVertex();

    EndPrimitive();
}