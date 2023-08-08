const GLchar* shader3D_textured_vert_buffer = "\
#version 300 es\n\
in highp vec3 vertex_position;\
in lowp vec2 vertexUV;\
in lowp vec3 vertex_color;\
uniform highp mat4 view_matrix;\
uniform highp vec3 position;\
uniform highp vec4 rotation;\
uniform lowp float scale;\
out lowp vec2 uv;\
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
    gl_Position = view_matrix * vec4(position + float4_rotate_float3(rotation, vertex_position * scale), 1.0);\
    fog_level = gl_Position.z;\
    uv = vertexUV;\
    vert_color = vertex_color;\
}";

const GLchar* shader3D_textured_frag_buffer = "\
#version 300 es\n\
uniform sampler2D tex;\
uniform lowp float brightness;\
uniform lowp vec4 fog_data;\
in lowp vec3 vert_color;\
in lowp vec2 uv;\
in highp float fog_level;\
out lowp vec3 color; \
\
void main() {\
    color = texture(tex, uv).xyz * vert_color * brightness;\
    lowp float fog_blend = 1.0 - exp2(-fog_data.w * fog_data.w * fog_level * fog_level);\
    color = mix(color, vec3(fog_data.x, fog_data.y, fog_data.z), fog_blend);\
}";
