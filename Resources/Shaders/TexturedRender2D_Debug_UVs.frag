#version 300 es

in lowp vec2 uv;
uniform lowp float brightness;
uniform sampler2D tex;
out lowp vec3 color;

void main()
{
    color = vec3(uv.x, uv.y, 0);
}