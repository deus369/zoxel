#version 320 es
layout(location=0) in lowp vec3 vertex_position;
uniform highp mat4 camera_matrix;
uniform highp mat4 transform_matrix;
out highp float fog_level;
out lowp vec3 mesh_pos;

void main() {
    gl_Position = camera_matrix * transform_matrix * vec4(vertex_position, 1);
    fog_level = gl_Position.z * gl_Position.z;
    mesh_pos = vertex_position;
}