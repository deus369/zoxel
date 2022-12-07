#version 300 es
uniform lowp float brightness;
out lowp vec4 color;

void main()
{
    color = vec4(0.08, 0.52, 0.34, 0) * brightness;
}