#version 300 es
//! Basic 3D Renderer

in lowp vec3 vertexPosition;
uniform lowp mat4 viewMatrix;
uniform lowp vec3 position;
uniform lowp vec4 rotation;
uniform lowp float scale;


vec3 float4_rotate_float3(vec4 rotation, vec3 value)
{
    vec3 rotationXYZ = rotation.xyz;
    vec3 t = cross(rotationXYZ, value) * 2.0f;
    vec3 crossB = cross(rotationXYZ, t);
    vec3 scaledT = t * rotation.w;
    return value + scaledT + crossB;
}

void main()
{
    gl_Position = viewMatrix * vec4(position + float4_rotate_float3(rotation, vertexPosition * scale), 1.0);
}