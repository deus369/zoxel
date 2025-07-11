/*const GLchar* shader_basic3D_vert_buffer = "\
#version 320 es\n\
layout(location=0) in lowp vec3 vertex_position;\
uniform highp mat4 camera_matrix;\
uniform highp mat4 transform_matrix;\
out highp float fog_level;\
\
void main() {\
    gl_Position = camera_matrix * transform_matrix * vec4(vertex_position, 1);\
    fog_level = gl_Position.z * gl_Position.z;\
}";

const GLchar* shader_basic3D_frag_buffer = "\
#version 320 es\n\
in highp float fog_level;\
uniform lowp vec4 fog_data;\
uniform lowp float brightness;\
out lowp vec3 frag_color; \
\
void main() {\
    frag_color = vec3(brightness, brightness / 3.0, brightness / 3.0);\
    lowp float fog_blend = min(1.0, 1.1 - exp2(-fog_data.w * fog_level));\
    frag_color = mix(frag_color, vec3(fog_data.x, fog_data.y, fog_data.z), fog_blend);\
}";*/

typedef struct {
    GLint vertex_position;
    GLuint transform_matrix;
    GLuint camera_matrix;
    GLuint fog_data;
    GLuint brightness;
} MaterialBasic3D;
zox_custom_component(MaterialBasic3D)

MaterialBasic3D create_MaterialBasic3D(const GLuint material) {
    return (MaterialBasic3D) {
        glGetAttribLocation(material, "vertex_position"),
        glGetUniformLocation(material, "transform_matrix"),
        glGetUniformLocation(material, "camera_matrix"),
        glGetUniformLocation(material, "fog_data"),
        glGetUniformLocation(material, "brightness")
    };
}
