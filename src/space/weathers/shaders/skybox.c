const GLchar* skybox_shader_source_vert = "\
#version 300 es\n\
in lowp vec3 vertex_position;\
uniform highp mat4 camera_matrix;\
uniform highp vec3 position;\
uniform lowp vec4 rotation;\
uniform lowp float scale;\
out lowp vec3 mesh_pos;\
\
vec3 float4_rotate_float3(vec4 rotation, vec3 value) {\
    vec3 rotationXYZ = rotation.xyz; \
    vec3 t = cross(rotationXYZ, value) * 2.0f; \
    vec3 crossB = cross(rotationXYZ, t); \
    vec3 scaledT = t * rotation.w; \
    return value + scaledT + crossB; \
}\
\
void main() {\
    gl_Position = camera_matrix * vec4(position + float4_rotate_float3(rotation, vertex_position * scale), 1.0);\
    lowp vec3 vertex_position2 = position + float4_rotate_float3(rotation, vertex_position * scale);\
    mesh_pos = vertex_position;\
}";

const GLchar* skybox_shader_source_frag = "\
#version 300 es\n\
uniform lowp float brightness;\
in lowp vec3 mesh_pos;\
out lowp vec4 color;\
\
void main() {\
    lowp vec3 sky_color_top = vec3(0.2, 0.6, 0.9);\
    lowp vec3 fog_color = vec3(0.7, 0.55, 0.58);\
    lowp float gradient = clamp((mesh_pos.y + 0.0) * 4.0, 0.0, 1.0);\
    if (mesh_pos.y > 0.0) {\
        if (abs(mesh_pos.x) > abs(mesh_pos.z)) {\
            sky_color_top.x = 1.0 - (abs(mesh_pos.x));\
        } else {\
            sky_color_top.x = 1.0 - (abs(mesh_pos.z));\
        }\
        sky_color_top.x -= 0.5 - mesh_pos.y;\
    }\
    color = vec4(mix(fog_color, sky_color_top, gradient), 1.0) * brightness;\
}";

// color.z -= color.x * 0.5;
// sky_color_top = vec3(0.2, 0.6, 0.9);
// mesh_y = (vertex_position.y + 0.02) * 4.0;
// lowp vec3 fog_color = vec3(2.0f / 255.0, 16.0f / 255.0, 24.0f / 255.0 );
// lowp vec3 fog_color = vec3(0.9, 0.95, 0.98);
// float3 fog_color = (float3) { 2.0f / 255.0f, 16.0f / 255.0f, 24.0f / 255.0f };
// lowp vec3 sky_color_bottom = vec3(0.9, 0.95, 0.98);
// color.x = color.y = 0.0; color.z = mesh_y;
// color = vec4(0, 0.6, 0.4, 1) * brightness;

uint2 shader_skybox;
uint material_skybox;

// todo: call dispose_line3D_shader / move it to a shader entity
void dispose_shader_skybox() {
    glDeleteShader(shader_skybox.x);
    glDeleteShader(shader_skybox.y);
    glDeleteProgram(material_skybox);
}

int load_shader_skybox() {
    //if (is_opengl_running()) {
        shader_skybox = spawn_gpu_shader_inline(skybox_shader_source_vert, skybox_shader_source_frag);
        material_skybox = spawn_gpu_material_program((const uint2) { shader_skybox.x, shader_skybox.y });
    //}
    return 0;
}