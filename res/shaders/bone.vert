#version 320 es
layout(location=0) in highp vec3 vertex_position;
layout(location=1) in highp vec3 vertex_color;
layout(location=2) in lowp float bone_index;
uniform highp mat4 camera_matrix;
uniform highp mat4 transform_matrix;
uniform highp mat4 bone_matrix[32];
uniform lowp vec3 bone_positions[32];
uniform lowp vec4 fog_data;
out lowp vec3 vertex_color_frag;
out lowp float fog_blend;

void main() {
    lowp int bone_index2 = int(bone_index * 255.0);
    highp mat4 bone = bone_matrix[bone_index2];
    lowp vec3 bone_position = bone_positions[bone_index2];
    vec4 transformed_position = bone * vec4(vertex_position - bone_position, 1);
    vec4 final_position = transformed_position;
    gl_Position = camera_matrix * transform_matrix * final_position;
    vertex_color_frag = vertex_color;
    highp float fog_level = gl_Position.z * gl_Position.z;
    fog_blend = min(1.0, 1.1 - exp2(-fog_data.w * fog_level));
}