// todo: load in .vert and .frag files as strings instead

const GLchar* shader_bone_vert = "\
#version 300 es\n\
layout(location=0) in highp vec3 vertex_position;\
layout(location=1) in highp vec3 vertex_color;\
uniform highp mat4 camera_matrix;\
uniform highp mat4 transform_matrix;\
uniform highp mat4 bone_matrix[2];\
uniform highp vec3 bone_positions[2];\
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

// note; this does update by delta... but now its not transforming at all!
// oh i get it, its where the bone initially sets in the mesh, and transform will be done from there
/*
 * vec4 skinned_position = vec4(0.0);
 * for (int i = 0; i < num_bones; ++i) {
 *    skinned_position += bone_weights[i] * (bone_matrices[i] * vec4(vertex_position, 1));
 * }
 * gl_Position = camera_matrix * skinned_position;
 * */
