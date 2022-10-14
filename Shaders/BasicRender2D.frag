#version 330

uniform float brightness;
out vec4 color;

void main()
{
    color = vec4(0.1, 0.65, 0.15, 0) * brightness;
}