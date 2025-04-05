const GLchar* shader3D_textured_vert_buffer = "\
#version 320 es\n\
layout(location=0) in lowp vec3 vertex_position;\
layout(location=1) in lowp vec2 vertex_uv;\
layout(location=2) in lowp vec3 vertex_color;\
uniform highp mat4 camera_matrix;\
uniform highp mat4 transform_matrix;\
out lowp vec2 uv;\
out lowp vec3 vertex_color_frag;\
out highp float fog_level;\
\
void main() {\
    gl_Position = camera_matrix * transform_matrix * vec4(vertex_position, 1);\
    uv = vertex_uv;\
    vertex_color_frag = vertex_color;\
    fog_level = gl_Position.z * gl_Position.z;\
}";

const GLchar* shader3D_textured_frag_buffer = "\
#version 320 es\n\
in lowp vec3 vertex_color_frag;\
in lowp vec2 uv;\
in highp float fog_level;\
uniform sampler2D tex;\
uniform lowp vec4 fog_data;\
uniform lowp float brightness;\
out lowp vec4 frag_color; \
\
void main() {\
    lowp vec4 texture_color = texture(tex, uv);\
    lowp vec3 mix_color = texture_color.xyz * vertex_color_frag * brightness;\
    lowp float fog_blend = min(1.0, 1.1 - exp2(-fog_data.w * fog_level));\
    mix_color = mix(mix_color, vec3(fog_data.x, fog_data.y, fog_data.z), fog_blend);\
    frag_color = vec4(mix_color, texture_color.w);\
}";

/*const GLchar* debug_shader3D_textured_frag_buffer = "\
#version 320 es\n\
uniform lowp vec4 fog_data;\
uniform lowp float brightness;\
in highp float fog_level;\
out lowp vec3 color; \
\
void main() {\
    color = vec3( 0.4, 0.4, 0.4 ) * brightness;\
    lowp float fog_blend = 1.0 - exp2(-fog_data.w * fog_data.w * fog_level * fog_level);\
    color = mix(color, vec3(fog_data.x, fog_data.y, fog_data.z), fog_blend);\
}";*/

/*
uniform highp vec3 position;\
uniform highp vec4 rotation;\
uniform lowp float scale;\

gl_Position = camera_matrix * vec4(position + float4_rotate_float3(rotation, vertex_position * scale), 1);\

vec3 float4_rotate_float3(vec4 rotation, vec3 value) {\
    vec3 rotationXYZ = rotation.xyz;\
    vec3 t = cross(rotationXYZ, value) * 2.0f;\
    vec3 crossB = cross(rotationXYZ, t);\
    vec3 scaledT = t * rotation.w;\
    return value + scaledT + crossB;\
}\*/

/*const GLchar* shader3D_textured_vert_buffer = "\
#version 320 es\n\
uniform highp mat4 camera_matrix;\
uniform highp vec3 position;\
uniform highp vec4 rotation;\
uniform lowp float scale;\
layout(location=0) in lowp vec3 vertex_position;\
layout(location=1) in lowp vec2 vertex_uv;\
layout(location=2) in lowp vec3 vertex_color;\
out lowp vec2 uv;\
out lowp vec3 vertex_color_frag;\
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
    gl_Position = camera_matrix * vec4(position + float4_rotate_float3(rotation, vertex_position * scale), 1);\
    fog_level = gl_Position.z;\
    uv = vertex_uv;\
    vertex_color_frag = vertex_color;\
}";

const GLchar* shader3D_textured_frag_buffer = "\
#version 320 es\n\
uniform sampler2D tex;\
uniform lowp vec4 fog_data;\
uniform lowp float brightness;\
in lowp vec3 vertex_color_frag;\
in lowp vec2 uv;\
in highp float fog_level;\
out lowp vec3 color; \
\
void main() {\
    color = texture(tex, uv).xyz * vertex_color_frag * brightness;\
    lowp float fog_blend = 1.0 - exp2(-fog_data.w * fog_data.w * fog_level * fog_level);\
    color = mix(color, vec3(fog_data.x, fog_data.y, fog_data.z), fog_blend);\
}";*/


// lowp float fog_blend = 1.0 - exp2(-fog_data.w * fog_data.w * fog_level * fog_level);
// color = mix(color, vec3(fog_data.x, fog_data.y, fog_data.z), fog_blend);
/*
const GLchar* shader3D_textured_vert_buffer = "\
#version 320 es\n\
layout(location=0) in highp vec3 vertex_position;\
void main() {\
    gl_Position = vec4(vertex_position.x, vertex_position.y, vertex_position.z, 1);\
}";

const GLchar* shader3D_textured_frag_buffer = "\
#version 320 es\n\
out lowp vec3 color;\
void main() {\
    color = vec3(0.2, 0.7, 0.4);\
}";
*/
