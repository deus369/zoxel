in lowp vec2 vertex_position;
uniform lowp mat4 camera_matrix;
uniform lowp vec3 position;
uniform lowp float angle;
uniform lowp float scale;

void main() {
    vec2 position2 = vec2(position.x, position.y);
    mat2 rotate = mat2(cos(angle), -sin(angle), sin(angle), cos(angle));
    gl_Position = camera_matrix * vec4(position2 + (rotate * vertex_position) * scale, position.z, 1.0);
}
