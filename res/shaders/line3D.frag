#version 320 es
in highp float fog_level;
uniform lowp vec4 color;
uniform lowp vec4 fog_data;
out lowp vec4 frag_color;

void main() {
    frag_color = color;
    lowp float fog_blend = min(1.0, 1.0 - exp2(-fog_data.w * fog_level));
    frag_color = mix(frag_color, vec4(fog_data.x, fog_data.y, fog_data.z, 0), fog_blend);
}