#version 320 es
in lowp vec3 vertex_color_frag;
in lowp float fog_blend;
uniform lowp vec4 fog_data;
uniform lowp float brightness;
out lowp vec3 frag_color;

void main() {
    frag_color = vertex_color_frag * brightness;
    frag_color = mix(frag_color, vec3(fog_data.x, fog_data.y, fog_data.z), fog_blend);
}