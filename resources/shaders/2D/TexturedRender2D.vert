#version 300 es

//! Textured 2D Renderer
in lowp vec2 vertexPosition;
in lowp vec2 vertexUV;
uniform lowp mat4 viewMatrix;
uniform lowp float positionX;
uniform lowp float positionY;
uniform lowp float angle;
uniform lowp float scale;
uniform lowp vec2 scale2;
out lowp vec2 uv;

void main()
{
    vec2 position = vec2(positionX, positionY);
    mat2 rotate = mat2(cos(angle), -sin(angle),
                       sin(angle), cos(angle));
    if (scale == 0.0)
    {
        vec2 vertexPosition2 = vertexPosition;
        vertexPosition2.x *= scale2.x;
        vertexPosition2.y *= scale2.y;
        gl_Position = viewMatrix * vec4(position + vertexPosition2, 0, 1.0);
        uv = vertexUV;
    }
    else
    {
        gl_Position = viewMatrix * vec4(position + (rotate * vertexPosition) * scale, 0, 1.0);
        uv = vertexUV;
    }
}