#version 300 es
// Basic 2D Renderer

in lowp vec2 point;
uniform lowp float pointX;
uniform lowp float pointY;
uniform lowp float angle;
uniform lowp float scale;

void main()
{
    vec2 position = vec2(pointX, pointY);
    mat2 rotate = mat2(cos(angle), -sin(angle),
                       sin(angle), cos(angle));
    gl_Position = vec4(position + (rotate * point) * scale, 0.0, 1.0);
}