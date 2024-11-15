// note; this does update by delta... but now its not transforming at all!
// oh i get it, its where the bone initially sets in the mesh, and transform will be done from there
/*
 * vec4 skinned_position = vec4(0.0);
 * for (int i = 0; i < num_bones; ++i) {
 *    skinned_position += bone_weights[i] * (bone_matrices[i] * vec4(vertex_position, 1));
 * }
 * gl_Position = camera_matrix * skinned_position;
 * */

// bone shader
// todo: load in .vert and .frag files as strings instead
const float test_bone_position = 0.48f;

#ifdef zox_enable_bones

const GLchar* shader3D_colored_vert_buffer = "\
#version 300 es\n\
layout(location=0) in highp vec3 vertex_position;\
layout(location=1) in highp vec3 vertex_color;\
uniform highp mat4 camera_matrix;\
uniform highp mat4 transform_matrix;\
uniform highp mat4 bone_matrix[2];\
uniform lowp vec4 fog_data;\
out lowp vec3 vertex_color_frag;\
out lowp float fog_blend;\
\
void main() {\
    highp mat4 bone = (vertex_position.y < 0.12) ? bone_matrix[0] : bone_matrix[1];\
    lowp vec3 original_bone_position = (vertex_position.y < 0.12) ? vec3(0, 0, 0) : vec3(0, 0.18, -0.03f);\
    vec4 transformed_position = bone * vec4(vertex_position - original_bone_position, 1);\
    vec4 final_position = transformed_position;\
    gl_Position = camera_matrix * transform_matrix * final_position;\
    vertex_color_frag = vertex_color;\
    highp float fog_level = gl_Position.z * gl_Position.z;\
    fog_blend = min(1.0, 1.1 - exp2(-fog_data.w * fog_level));\
}";

#else

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

#endif

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

// frag_color = vec4(1, 0, 0, 0.2)
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
