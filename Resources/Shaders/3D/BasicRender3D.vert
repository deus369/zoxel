#version 300 es
//! Basic 3D Renderer

in lowp vec3 vertexPosition;
uniform lowp mat4 viewMatrix;
uniform lowp vec3 position;
// uniform lowp float angle;
uniform lowp float scale;

void main()
{
    //mat2 rotate = mat2(cos(angle), -sin(angle),
    //                   sin(angle), cos(angle));
    //gl_Position = viewMatrix * vec4(position + (rotate * vertexPosition) * scale, 0, 1.0);
    
    //! \todo Rotate the thing! Maybe just add in a transform matrix.
    gl_Position = viewMatrix * vec4(position + (vertexPosition) * scale, 1.0);
}