#version 300 es

in lowp vec2 uv;
uniform lowp float brightness;
uniform sampler2D tex;
out lowp vec3 color;

void main()
{
    color = texture(tex, uv).xyz * brightness;
}