#ifdef zox_transparent_voxes

const GLchar* shader_bone_frag = "\
#version 320 es\n\
in lowp vec3 vertex_color_frag;\
in lowp float fog_blend;\
uniform lowp vec4 fog_data;\
uniform lowp float brightness;\
out lowp vec4 frag_color;\
\
void main() {\
    lowp vec3 frag_color3 = vertex_color_frag * brightness;\
    frag_color3 = mix(frag_color3, vec3(fog_data.x, fog_data.y, fog_data.z), fog_blend);\
    frag_color = vec4(frag_color3.x, frag_color3.y, frag_color3.z, 0.4);\
}";

#else

const GLchar* shader_bone_frag = "\
#version 320 es\n\
in lowp vec3 vertex_color_frag;\
in lowp float fog_blend;\
uniform lowp vec4 fog_data;\
uniform lowp float brightness;\
out lowp vec3 frag_color;\
\
void main() {\
    frag_color = vertex_color_frag * brightness;\
    frag_color = mix(frag_color, vec3(fog_data.x, fog_data.y, fog_data.z), fog_blend);\
}";

#endif
