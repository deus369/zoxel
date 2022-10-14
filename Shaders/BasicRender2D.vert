#version 330
// Basic 2D Renderer

in vec2 point;
uniform float pointX;
uniform float pointY;
uniform float angle;
uniform float scale;

void main()
{
    vec2 position = vec2(pointX, pointY);
    mat2 rotate = mat2(cos(angle), -sin(angle),
                       sin(angle), cos(angle));
    gl_Position = vec4(position + (rotate * point) * scale, 0.0, 1.0);
}