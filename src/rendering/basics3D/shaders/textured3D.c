/*const GLchar* debug_shader3D_textured_frag_buffer = "\
#version 320 es\n\
uniform lowp vec4 fog_data;\
uniform lowp float brightness;\
in highp float fog_level;\
out lowp vec3 color; \
\
void main() {\
    color = vec3( 0.4, 0.4, 0.4 ) * brightness;\
    lowp float fog_blend = 1.0 - exp2(-fog_data.w * fog_data.w * fog_level * fog_level);\
    color = mix(color, vec3(fog_data.x, fog_data.y, fog_data.z), fog_blend);\
}";*/

/*
uniform highp vec3 position;\
uniform highp vec4 rotation;\
uniform lowp float scale;\

gl_Position = camera_matrix * vec4(position + float4_rotate_float3(rotation, vertex_position * scale), 1);\

vec3 float4_rotate_float3(vec4 rotation, vec3 value) {\
    vec3 rotationXYZ = rotation.xyz;\
    vec3 t = cross(rotationXYZ, value) * 2.0f;\
    vec3 crossB = cross(rotationXYZ, t);\
    vec3 scaledT = t * rotation.w;\
    return value + scaledT + crossB;\
}\*/


// lowp float fog_blend = 1.0 - exp2(-fog_data.w * fog_data.w * fog_level * fog_level);
// color = mix(color, vec3(fog_data.x, fog_data.y, fog_data.z), fog_blend);
/*
const GLchar* shader3D_textured_vert_buffer = "\
#version 320 es\n\
layout(location=0) in highp vec3 vertex_position;\
void main() {\
    gl_Position = vec4(vertex_position.x, vertex_position.y, vertex_position.z, 1);\
}";

const GLchar* shader3D_textured_frag_buffer = "\
#version 320 es\n\
out lowp vec3 color;\
void main() {\
    color = vec3(0.2, 0.7, 0.4);\
}";
*/
