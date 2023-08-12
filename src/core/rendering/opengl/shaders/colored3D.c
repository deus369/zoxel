const GLchar* shader3D_colored_vert_buffer = "\
#version 300 es\n\
in highp vec3 vertex_position;\
in lowp vec3 vertex_color;\
uniform highp mat4 camera_matrix;\
uniform highp vec3 position;\
uniform highp vec4 rotation;\
uniform highp float scale;\
out lowp vec3 vert_color;\
out highp float fog_level;\
\
vec3 float4_rotate_float3(vec4 rotation, vec3 value) {\
    vec3 rotationXYZ = rotation.xyz;\
    vec3 t = cross(rotationXYZ, value) * 2.0f;\
    vec3 crossB = cross(rotationXYZ, t);\
    vec3 scaledT = t * rotation.w;\
    return value + scaledT + crossB;\
}\
\
void main() {\
    gl_Position = camera_matrix * vec4(position + float4_rotate_float3(rotation, vertex_position * scale), 1.0);\
    fog_level = gl_Position.z;\
    vert_color = vertex_color;\
}";

const GLchar* shader3D_colored_frag_buffer = "\
#version 300 es\n\
in lowp vec3 vert_color;\
in highp float fog_level;\
uniform lowp float brightness; \
uniform lowp vec4 fog_data;\
out lowp vec3 color;\
\
void main() {\
    color = vert_color * brightness;\
    lowp float fog_blend = 1.0 - exp2(-fog_data.w * fog_data.w * fog_level * fog_level);\
    color = mix(color, vec3(fog_data.x, fog_data.y, fog_data.z), fog_blend);\
}";
