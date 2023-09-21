const GLchar* skybox_shader_source_vert = "\
#version 300 es\n\
#extension GL_ARB_explicit_uniform_location : require\n\
in lowp vec3 vertex_position;\
layout(location=0) uniform highp mat4 camera_matrix;\
layout(location=1) uniform highp vec3 position;\
layout(location=2) uniform lowp vec4 rotation;\
layout(location=3) uniform lowp float scale;\
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
#extension GL_ARB_explicit_uniform_location : require\n\
layout(location=4) uniform lowp float brightness;\
layout(location=5) uniform lowp vec3 sky_color;\
layout(location=6) uniform lowp vec3 sky_bottom_color;\
in lowp vec3 mesh_pos;\
out lowp vec3 color;\
\
void main() {\
    lowp vec3 sky_top_color = sky_color;\
    lowp float gradient = clamp((mesh_pos.y + 0.0) * 4.0, 0.0, 1.0);\
    if (mesh_pos.y > 0.0) {\
        if (abs(mesh_pos.x) > abs(mesh_pos.z)) {\
            sky_top_color.x = 1.0 - (abs(mesh_pos.x));\
        } else {\
            sky_top_color.x = 1.0 - (abs(mesh_pos.z));\
        }\
        sky_top_color.x -= 0.5 - mesh_pos.y;\
    }\
    color = vec3(mix(sky_bottom_color, sky_top_color, gradient)) * brightness;\
}";

// lowp vec3 fog_color = vec3(0.7, 0.55, 0.58);
//  color = sky_color;
// lowp vec3 sky_color = vec3(0.2, 0.6, 0.9);
// color.z -= color.x * 0.5;
// sky_color = vec3(0.2, 0.6, 0.9);
// mesh_y = (vertex_position.y + 0.02) * 4.0;
// lowp vec3 fog_color = vec3(2.0f / 255.0, 16.0f / 255.0, 24.0f / 255.0 );
// lowp vec3 fog_color = vec3(0.9, 0.95, 0.98);
// float3 fog_color = (float3) { 2.0f / 255.0f, 16.0f / 255.0f, 24.0f / 255.0f };
// lowp vec3 sky_color_bottom = vec3(0.9, 0.95, 0.98);
// color.x = color.y = 0.0; color.z = mesh_y;
// color = vec4(0, 0.6, 0.4, 1) * brightness;

GLuint2 shader_skybox;

// todo: call dispose_line3D_shader / move it to a shader entity
void dispose_shader_skybox() {
    glDeleteShader(shader_skybox.x);
    glDeleteShader(shader_skybox.y);
}

void set_sky_color(ecs_world_t *world, float3 top_color, float3 bottom_color) {
    GLuint material = ecs_get(world, skybox, MaterialGPULink)->value;
    opengl_set_material(material);
    opengl_set_float3(5, top_color);
    opengl_set_float3(6, bottom_color);
    opengl_set_material(0);
    // zoxel_log(" > set sky color [%fx%fx%f]\n", color.x, color.y, color.z);
}

int load_shader_skybox() {
    shader_skybox = spawn_gpu_shader_inline(skybox_shader_source_vert, skybox_shader_source_frag);
    return 0;
}