const GLchar* shader3D_colored_vert_buffer = "\
#version 300 es\n\
layout(location=0) in highp vec3 vertex_position;\
layout(location=1) in highp vec3 vertex_color;\
uniform highp mat4 camera_matrix;\
uniform highp mat4 transform_matrix;\
uniform lowp vec4 fog_data;\
out lowp vec3 vertex_color_frag;\
out lowp float fog_blend;\
\
void main() {\
    gl_Position = camera_matrix * transform_matrix * vec4(vertex_position, 1);\
    vertex_color_frag = vertex_color;\
    highp float fog_level = gl_Position.z * gl_Position.z;\
    fog_blend = min(1.0, 1.1 - exp2(-fog_data.w * fog_level));\
}";

/*
uniform highp vec3 position;\
uniform highp vec4 rotation;\
uniform highp float scale;\
vec3 float4_rotate_float3(vec4 rotation, vec3 value) {\
    vec3 rotationXYZ = rotation.xyz;\
    vec3 t = cross(rotationXYZ, value) * 2.0f;\
    vec3 crossB = cross(rotationXYZ, t);\
    vec3 scaledT = t * rotation.w;\
    return value + scaledT + crossB;\
}\
*/

// camera_matrix * vec4(position + float4_rotate_float3(rotation, vertex_position * scale), 1);

#ifdef zox_transparent_voxes

const GLchar* shader3D_colored_frag_buffer = "\
#version 300 es\n\
in lowp vec3 vertex_color_frag;\
in lowp float fog_blend;\
uniform lowp vec4 fog_data;\
uniform lowp float brightness;\
out lowp vec4 frag_color;\
\
void main() {\
    lowp vec3 frag_color3 = vertex_color_frag * brightness;\
    frag_color3 = mix(frag_color3, vec3(fog_data.x, fog_data.y, fog_data.z), fog_blend);\
    frag_color = vec4(frag_color3.x, frag_color3.y, frag_color3.z, 0.4);\
}";

#else

const GLchar* shader3D_colored_frag_buffer = "\
#version 300 es\n\
in lowp vec3 vertex_color_frag;\
in lowp float fog_blend;\
uniform lowp vec4 fog_data;\
uniform lowp float brightness;\
out lowp vec3 frag_color;\
\
void main() {\
    frag_color = vertex_color_frag * brightness;\
    frag_color = mix(frag_color, vec3(fog_data.x, fog_data.y, fog_data.z), fog_blend);\
}";

#endif

// test fog color:
// color = vec3(fog_data.x, fog_data.y, fog_data.z);

// test to remove memory bug

const GLchar* debug_shader3D_colored_vert_buffer = "\
#version 300 es\n\
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
#version 300 es\n\
out lowp vec3 color;\
\
void main() {\
    color = vec3(0.8, 0.3, 0.45);\
}";
