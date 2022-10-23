#version 300 es
//! Textured 2D Renderer

in lowp vec2 positionOffset;
uniform lowp mat4 viewMatrix;
uniform lowp float positionX;
uniform lowp float positionY;
uniform lowp float angle;
uniform lowp float scale;

void main()
{
    vec2 position = vec2(positionX, positionY);
    mat2 rotate = mat2(cos(angle), -sin(angle),
                       sin(angle), cos(angle));
    gl_Position = viewMatrix * vec4(position + (rotate * positionOffset) * scale, 0, 1.0);
}