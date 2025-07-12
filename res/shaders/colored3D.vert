#version 320 es
layout(location=0) in highp vec3 vertex_position;
layout(location=1) in highp vec3 vertex_color;
uniform highp mat4 transform_matrix;
uniform highp mat4 camera_matrix;
uniform lowp vec4 fog_data;
out lowp vec3 vertex_color_frag;
out lowp float fog_blend;

void main() {
    gl_Position = camera_matrix * transform_matrix * vec4(vertex_position, 1);
    vertex_color_frag = vertex_color;
    highp float fog_level = gl_Position.z * gl_Position.z;
    fog_blend = min(1.0, 1.1 - exp2(-fog_data.w * fog_level));
}