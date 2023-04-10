const char* line3D_source_vert = "\
#version 300 es\n\
in highp vec3 position;\
uniform highp mat4 camera_matrix;\
out highp float fog_level;\
\
void main() {\
    gl_Position = camera_matrix * vec4(position, 1);\
    fog_level = gl_Position.z;\
}";

const GLchar* line3D_source_frag = "\
#version 300 es\n\
in highp float fog_level;\
uniform lowp vec3 color;\
uniform lowp vec4 fog_data;\
out lowp vec3 color2;\
\
void main() {\
    color2 = color;\
    lowp float fog_blend = 1.0 - exp2(-fog_data.w * fog_data.w * fog_level * fog_level);\
    color2 = mix(color2, vec3(fog_data.x, fog_data.y, fog_data.z), fog_blend);\
}";
