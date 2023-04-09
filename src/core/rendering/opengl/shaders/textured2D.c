const GLchar* shader2D_textured_vert_buffer = "\
#version 300 es\n\
in lowp vec2 vertexPosition;\
in lowp vec2 vertexUV;\
uniform lowp mat4 viewMatrix;\
uniform lowp float positionX;\
uniform lowp float positionY;\
uniform lowp float positionZ;\
uniform lowp float angle;\
uniform lowp float scale;\
out lowp vec2 uv;\
\
void main() {\
    vec2 position = vec2(positionX, positionY);\
    mat2 rotate = mat2(cos(angle), -sin(angle), sin(angle), cos(angle));\
    gl_Position = viewMatrix * vec4(position + (rotate * vertexPosition) * scale, positionZ, 1.0);\
    uv = vertexUV;\
}";

const GLchar* shader2D_textured_frag_buffer = "\
#version 300 es\n\
in lowp vec2 uv;\
uniform lowp float brightness;\
uniform sampler2D tex;\
out lowp vec4 color;\
\
void main() {\
    color = texture(tex, uv) * brightness;\
}";
