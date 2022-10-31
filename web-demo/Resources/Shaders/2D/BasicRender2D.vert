#version 300 es
//! Basic 2D Renderer

// layout (location = 0)
in lowp vec2 vertexPosition;
uniform lowp mat4 viewMatrix;
uniform lowp float positionX;
uniform lowp float positionY;
uniform lowp float angle;
uniform lowp float scale;
// uniform lowp mat4 MVP; gl_ModelViewProjectionMatrix * 

// mat4 CalculateMatrix(vec3 position, vec3 rot)
// {
//     float foo = 1.0;
//     float bar = 0.0;
//     return mat4(position.x, position.y, position.z, 0.0,
//                 rot.x,      rot.y,      rot.z,      0.0,
//                 foo,        bar,        foo,        bar,
//                 0.0,        0.0,        0.0,        1.0);
// }

void main()
{
    vec2 position = vec2(positionX, positionY);
    mat2 rotate = mat2(cos(angle), -sin(angle),
                       sin(angle), cos(angle));
    gl_Position = viewMatrix * vec4(position + (rotate * vertexPosition) * scale, 0, 1.0); // 
}

    //pos.x = pos.x + position.x;
    //pos.y = pos.y + position.y;
    //gl_Position = viewMatrix * pos; // vec4(position.x, position.y, 0, 0);

    // gl_Position = viewMatrix * vec4(position + (rotate * positionOffset) * scale, 0.0, 1.0);

    // vec2 offset = vec2(pointX, pointY);
    //mat2 rotate = mat2(cos(angle), -sin(angle),
    //                   sin(angle), cos(angle));
    // gl_Position = vec4(offset + (rotate * position) * scale, 0.0, 1.0);
    // gl_Position = vec4(position + (rotate * scale), 0.0, 1.0);
    // gl_Position = CalculateMatrix(position, vec3(0.0, 0.0, 0.0)) * vec4(position, 1.0);