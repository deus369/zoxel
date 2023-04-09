const GLchar* shader2D_basic_vert_buffer = "\
#version 300 es\n\
in lowp vec2 vertexPosition;\
uniform lowp mat4 viewMatrix;\
uniform lowp float positionX;\
uniform lowp float positionY;\
uniform lowp float angle;\
uniform lowp float scale;\
\
void main() {\
    vec2 position = vec2(positionX, positionY);\
    mat2 rotate = mat2(cos(angle), -sin(angle), sin(angle), cos(angle));\
    gl_Position = viewMatrix * vec4(position + (rotate * vertexPosition) * scale, 0, 1.0);\
}";

const GLchar* shader2D_basic_frag_buffer = "\
#version 300 es\n\
uniform lowp float brightness;\
out lowp vec4 color;\
\
void main() {\
    color = vec4(0.5, 0.65, 0.15, 0) * brightness;\
}";
