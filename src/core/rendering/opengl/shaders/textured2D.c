
const GLchar* shader2D_textured_vert_buffer = "\
#version 300 es\n\
in lowp vec2 vertexPosition;\
in lowp vec2 vertexUV;\
uniform lowp mat4 camera_matrix;\
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
    gl_Position = camera_matrix * vec4(position + (rotate * vertexPosition) * scale, positionZ, 1.0);\
    uv = vertexUV;\
}";

const GLchar* shader2D_textured_frag_buffer = "\
#version 300 es\n\
uniform sampler2D tex;\
in lowp vec2 uv;\
uniform lowp float brightness;\
out lowp vec4 color;\
\
void main() {\
    color = texture(tex, uv) * brightness;\
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
in lowp vec2 vertexPosition;\
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
    gl_Position = camera_matrix * vec4(position + (rotate * vertexPosition) * scale, positionZ, 1.0);\
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