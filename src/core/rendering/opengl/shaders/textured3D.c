const GLchar* shader3D_textured_vert_buffer = "\
#version 300 es\n\
uniform highp mat4 camera_matrix;\
uniform highp vec3 position;\
uniform highp vec4 rotation;\
uniform lowp float scale;\
layout(location=0) in highp vec3 vertex_position;\
layout(location=1) in lowp vec2 vertex_uv;\
layout(location=2) in lowp vec3 vertex_color;\
out lowp vec2 uv;\
out lowp vec3 vertex_color_frag;\
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
    uv = vertex_uv;\
    vertex_color_frag = vertex_color;\
}";

const GLchar* shader3D_textured_frag_buffer = "\
#version 300 es\n\
uniform sampler2D tex;\
uniform lowp float brightness;\
uniform lowp vec4 fog_data;\
in lowp vec3 vertex_color_frag;\
in lowp vec2 uv;\
in highp float fog_level;\
out lowp vec3 color; \
\
void main() {\
    color = texture(tex, uv).xyz * vertex_color_frag * brightness;\
    lowp float fog_blend = 1.0 - exp2(-fog_data.w * fog_data.w * fog_level * fog_level);\
    color = mix(color, vec3(fog_data.x, fog_data.y, fog_data.z), fog_blend);\
}";
