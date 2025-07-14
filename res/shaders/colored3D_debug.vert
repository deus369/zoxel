layout(location=0) in lowp vec3 vertex_position;
uniform lowp mat4 camera_matrix;
uniform lowp vec3 position;
uniform lowp vec4 rotation;

vec3 float4_rotate_float3(vec4 rotation, vec3 value) {
    vec3 rotationXYZ = rotation.xyz;
    vec3 t = cross(rotationXYZ, value) * 2.0f;
    vec3 crossB = cross(rotationXYZ, t);
    vec3 scaledT = t * rotation.w;
    return value + scaledT + crossB;
}

void main() {
    gl_Position = camera_matrix * vec4(position + float4_rotate_float3(rotation, vertex_position), 1);
}