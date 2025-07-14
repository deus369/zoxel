in highp vec3 position;
uniform highp mat4 camera_matrix;
out highp float fog_level;

void main() {
    gl_Position = camera_matrix * vec4(position, 1);
    fog_level = gl_Position.z * gl_Position.z;
}