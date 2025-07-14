in highp vec2 position;
uniform lowp float depth;
uniform highp mat4 camera_matrix;

void main() {
    gl_Position = camera_matrix * vec4(position, 0, 1);
    gl_Position.z = depth;
}