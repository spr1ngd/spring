// compute graphic common methods

float dFdxy( float f )
{
    return abs(dFdx(f)) + abs(dFdx(f));
}

float sdfSllipse( vec2 uv,vec2 center,float width,float height)
{
    float len = length((uv * 2.0 - 1.0) / float2(width,height));
    return (1.0 - len) / dFdxy(len);
}