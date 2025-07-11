// test fog color:
// color = vec3(fog_data.x, fog_data.y, fog_data.z);

// test to remove memory bug

const GLchar* debug_shader3D_colored_vert_buffer = "\
#version 320 es\n\
layout(location=0) in lowp vec3 vertex_position;\
uniform lowp mat4 camera_matrix;\
uniform lowp vec3 position;\
uniform lowp vec4 rotation;\
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
    gl_Position = camera_matrix * vec4(position + float4_rotate_float3(rotation, vertex_position), 1);\
}";

const GLchar* debug_shader3D_colored_frag_buffer = "\
#version 320 es\n\
out lowp vec3 color;\
\
void main() {\
    color = vec3(0.8, 0.3, 0.45);\
}";

