const GLchar* shader2D_basic_vert_buffer = "\
#version 300 es\n\
in lowp vec2 vertex_position;\
uniform lowp mat4 camera_matrix;\
uniform lowp vec3 position;\
uniform lowp float angle;\
uniform lowp float scale;\
\
void main() {\
    vec2 position2 = vec2(position.x, position.y);\
    mat2 rotate = mat2(cos(angle), -sin(angle), sin(angle), cos(angle));\
    gl_Position = camera_matrix * vec4(position2 + (rotate * vertex_position) * scale, position.z, 1.0);\
}";

const GLchar* shader2D_basic_frag_buffer = "\
#version 300 es\n\
uniform lowp float brightness;\
out lowp vec4 color;\
\
void main() {\
    color = vec4(0.5, 0.65, 0.15, 0) * brightness;\
}";
