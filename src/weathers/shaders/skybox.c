// #extension GL_ARB_explicit_uniform_location : enable\n
// layout(location=4) 

const GLchar* skybox_shader_source_vert = "\
#version 320 es\n\
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
#version 320 es\n\
uniform lowp float brightness;\
uniform lowp vec3 sky_top_color;\
uniform lowp vec3 sky_bottom_color;\
uniform lowp float time;\
in lowp vec3 mesh_pos;\
out lowp vec3 color;\
\
lowp float rand(lowp vec2 co) {\
    return fract(sin(dot(co, vec2(12.9898,78.233))) * 43758.5453);\
}\
\
lowp vec3 sky_gradient(lowp vec3 color) {\
    if (mesh_pos.y > 0.1) {\
        lowp float height_power = (mesh_pos.y - 0.1) * (1.0 - abs(max(mesh_pos.x, mesh_pos.z))) * 1.1;\
        color.x += height_power;\
        color.y += height_power;\
        color.z += height_power;\
        if (mesh_pos.x >= -0.1 && mesh_pos.x <= 0.1 && mesh_pos.z >= -0.1 && mesh_pos.z <= 0.1) {\
            lowp float to_mid_power = (1.0 - 10.0 * max(abs(mesh_pos.x), abs(mesh_pos.z)));\
            color.x += to_mid_power;\
            color.y += to_mid_power;\
            color.z += to_mid_power;\
            lowp float noise2 = rand(time * mesh_pos.xy);\
            color -= vec3(noise2) * 1.4;\
        }\
    }\
    return color;\
}\
\
void main() {\
    lowp vec3 sky_top_color2 = sky_top_color;\
    lowp float gradient = clamp((mesh_pos.y + 0.0) * 4.0, 0.0, 1.0);\
    color = vec3(mix(sky_bottom_color, sky_top_color2, gradient)) * brightness;\
    color = sky_gradient(color);\
    color -= vec3(1) * 0.05;\
    lowp float noise = rand(time * mesh_pos.xy);\
    color += vec3(noise) * 0.1;\
}";

/*
void main() {\
    lowp vec3 sky_top_color2 = sky_top_color;\
    lowp float gradient = clamp((mesh_pos.y + 0.0) * 4.0, 0.0, 1.0);\
    color = vec3(mix(sky_bottom_color, sky_top_color2, gradient)) * brightness;\
    if (mesh_pos.y > 0.0) {\
        lowp float height_power = mesh_pos.y * (1.0 - abs(max(mesh_pos.x, mesh_pos.z))) * 1.1;\
        color.x += height_power;\
        color.y += height_power;\
        color.z += height_power;\
        if (mesh_pos.x >= -0.1 && mesh_pos.x <= 0.1 && mesh_pos.z >= -0.1 && mesh_pos.z <= 0.1) {\
            lowp float to_mid_power = (1.0 - 10.0 * max(abs(mesh_pos.x), abs(mesh_pos.z)));\
            color.x += to_mid_power;\
            color.y += to_mid_power;\
            color.z += to_mid_power;\
            lowp float noise2 = rand(time * mesh_pos.xy);\
            color -= vec3(noise2) * 1.4;\
        }\
    }\
    lowp float noise = rand(time * mesh_pos.xy);\
    color += vec3(noise) * 0.18;\
}";

*/
/*
    lowp float time = mod(gl_FragCoord.y, 100.0) * 0.01;\

if (abs(mesh_pos.x) > abs(mesh_pos.z)) {\
    sky_top_color2.x = 1.0 - (abs(mesh_pos.x));\
} else {\
    sky_top_color2.x = 1.0 - (abs(mesh_pos.z));\
}\
sky_top_color2.x -= 0.5 - mesh_pos.y;\
*/

ecs_entity_t spawn_shader_skybox(ecs_world_t *world) {
    const byte shader_index = get_new_shader_source_index();
    shader_verts[shader_index] = skybox_shader_source_vert;
    shader_frags[shader_index] = skybox_shader_source_frag;
    const ecs_entity_t e = spawn_shader(world, shader_index);
    zox_name("shader_skybox")
    return e;
}
