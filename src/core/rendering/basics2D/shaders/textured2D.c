
const GLchar* shader2D_textured_vert_buffer = "\
#version 300 es\n\
layout(location=0) in lowp vec2 vertex_position;\
layout(location=1) in lowp vec2 vertex_uv;\
out lowp vec2 uv;\
uniform highp mat4 camera_matrix;\
uniform lowp vec3 position;\
uniform lowp float angle;\
uniform lowp float scale;\
\
void main() {\
    vec2 position2 = vec2(position.x, position.y);\
    mat2 rotate = mat2(cos(angle), -sin(angle), sin(angle), cos(angle));\
    gl_Position = camera_matrix * vec4(position2 + (rotate * vertex_position) * scale, position.z, 1.0);\
    uv = vertex_uv;\
}";

const GLchar* shader2D_textured_frag_buffer = "\
#version 300 es\n\
in lowp vec2 uv;\
out lowp vec4 color;\
uniform sampler2D tex;\
uniform lowp float brightness;\
uniform lowp float alpha;\
\
void main() {\
    color = texture(tex, uv) * brightness;\
    color.w *= alpha;\
}";

// testing uvs:
//  color = vec4(uv.x, uv.y, 0, 1);
// proper colors:
//  color = texture(tex, uv) * brightness;
// straight color:
//  color = vec4(0, 1, 1, 1) * brightness;

/*
const GLchar* shader2D_textured_vert_buffer = "\
#version 300 es\n\
in lowp vec2 vertex_position;\
uniform lowp mat4 camera_matrix;\
uniform lowp float positionX;\
uniform lowp float positionY;\
uniform lowp float positionZ;\
uniform lowp float angle;\
uniform lowp float scale;\
\
void main() {\
    vec2 position = vec2(positionX, positionY);\
    mat2 rotate = mat2(cos(angle), -sin(angle), sin(angle), cos(angle));\
    gl_Position = camera_matrix * vec4(position + (rotate * vertex_position) * scale, positionZ, 1.0);\
}";

const GLchar* shader2D_textured_frag_buffer = "\
#version 300 es\n\
uniform lowp float brightness;\
out lowp vec4 color;\
\
void main() {\
    color = vec4(0, 1, 1, 1) * brightness;\
}";
*/