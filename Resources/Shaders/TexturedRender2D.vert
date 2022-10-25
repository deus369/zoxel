#version 300 es

//! Textured 2D Renderer
layout (location = 0) in lowp vec2 vertexPosition;
layout (location = 1) in lowp vec2 vertexUV;
uniform lowp mat4 viewMatrix;
uniform lowp float positionX;
uniform lowp float positionY;
uniform lowp float angle;
uniform lowp float scale;
out vec2 uv;

void main()
{
    vec2 position = vec2(positionX, positionY);
    uv = vertexUV; // vec2(0.0, 0.0); // vertexUV;
    /*if (vertexPosition.x > 0.0)
    {
        uv.x = 1.0;
    }
    if (vertexPosition.y > 0.0)
    {
        uv.y = 1.0;
    }*/
    mat2 rotate = mat2(cos(angle), -sin(angle),
                       sin(angle), cos(angle));
    gl_Position = viewMatrix * vec4(position + (rotate * vertexPosition) * scale, 0, 1.0);
}