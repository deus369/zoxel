layout(location=0) in lowp vec3 vertex_position;
layout(location=1) in lowp vec2 vertex_uv;
layout(location=2) in lowp vec3 vertex_color;
uniform highp mat4 camera_matrix;
uniform highp mat4 transform_matrix;
out lowp vec2 uv;
out lowp vec3 vertex_color_frag;
out highp float fog_level;

void main() {
    gl_Position = camera_matrix * transform_matrix * vec4(vertex_position, 1);
    uv = vertex_uv;
    vertex_color_frag = vertex_color;
    fog_level = gl_Position.z * gl_Position.z;
}