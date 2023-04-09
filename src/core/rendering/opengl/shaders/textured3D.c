const GLchar* shader3D_textured_vert_buffer = "\
#version 300 es\n\
in highp vec3 vertexPosition;\
in highp vec2 vertexUV;\
uniform highp mat4 view_matrix;\
uniform highp vec3 position;\
uniform highp vec4 rotation;\
uniform highp float scale;\
out highp vec2 uv;\
out highp float fog_level;\
\
vec3 float4_rotate_float3(vec4 rotation, vec3 value) {\
    vec3 rotationXYZ = rotation.xyz;\
    vec3 t = cross(rotationXYZ, value) * 2.0f;\
    vec3 crossB = cross(rotationXYZ, t);\
    vec3 scaledT = t * rotation.w;\
    return value + scaledT + crossB;\
}\
\
void main() {\
    gl_Position = view_matrix * vec4(position + float4_rotate_float3(rotation, vertexPosition * scale), 1.0);\
    uv = vertexUV;\
    fog_level = gl_Position.z;\
}";

const GLchar* shader3D_textured_frag_buffer = "\
#version 300 es\n\
uniform highp float brightness;\
uniform sampler2D tex;\
in highp vec2 uv;\
in highp float fog_level;\
out highp vec4 color; \
\
void main() {\
    color = texture(tex, uv) * brightness; \
    highp vec4 backgroundColor = vec4(2.0f / 255.0f, 16.0f / 255.0f, 24.0f / 255.0f, 1);\
    highp float fog_density = 0.0126;\
    highp float fogBlend = 1.0 - exp2(-fog_density * fog_density * fog_level * fog_level);\
    color = mix(color, backgroundColor, fogBlend);\
}";
