uniform lowp vec4 fog_data;
in highp float fog_level;
in lowp vec4 frag_color;
out lowp vec4 color_output;

void main() {
    lowp float fog_blend = 1.0 - exp2(-fog_data.w * fog_level * fog_level);
    color_output = vec4(mix(frag_color.xyz, vec3(fog_data.x, fog_data.y, fog_data.z), fog_blend), frag_color.w);
}