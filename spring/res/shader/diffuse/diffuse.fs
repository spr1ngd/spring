
uniform vec4 Main_Color;
uniform vec4 AmbientColor;

void main()
{
    // ambient 
    vec4 ambient = AmbientColor;

    // diffuse 
    
    gl_FragColor = AmbientColor;
}