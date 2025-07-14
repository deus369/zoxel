uniform highp mat4 camera_matrix;
uniform lowp vec3 position;
uniform lowp float angle;
uniform lowp float scale;
layout(location=0) in lowp vec2 vertex_position;
layout(location=1) in lowp vec2 vertex_uv;
out lowp vec2 uv;

void main() {
    mat2 rotate = mat2(cos(angle), -sin(angle), sin(angle), cos(angle));
    gl_Position = camera_matrix * vec4(vec2(position.x, position.y) + (rotate * vertex_position) * scale, 0, 1.0);
    gl_Position.z = position.z;
    uv = vertex_uv;
}