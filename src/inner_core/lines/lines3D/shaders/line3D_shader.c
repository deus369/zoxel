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
uniform highp vec4 color;\
out highp vec4 color_output;\
in highp float fog_level;\
\
void main() {\
    color_output = color;\
    highp vec4 backgroundColor = vec4(2.0f / 255.0f, 16.0f / 255.0f, 24.0f / 255.0f, 1);\
    highp float fog_density = 0.0126;\
    highp float fogBlend = 1.0 - exp2(-fog_density * fog_density * fog_level * fog_level);\
    color_output = mix(color_output, backgroundColor, fogBlend);\
}";
