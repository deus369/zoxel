#version 300 es

uniform lowp float brightness;
out lowp vec4 color;

void main()
{
    color = vec4(0.3, 0.85, 0.25, 0) * brightness;
}