in highp vec3 position;
in lowp vec4 color;
uniform highp mat4 camera_matrix;
uniform highp float thickness;
out highp float fog_level;
out lowp vec4 frag_color;

void main() {
    gl_Position = camera_matrix * vec4(position, 1.0);
    fog_level = gl_Position.z;
    highp float distance_to_camera = distance(vec3(0, 0, 0), gl_Position.xyz);
    gl_PointSize = thickness / distance_to_camera;
    frag_color = color;
}