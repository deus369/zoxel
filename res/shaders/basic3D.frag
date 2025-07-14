in highp float fog_level;
uniform lowp vec4 fog_data;
uniform lowp float brightness;
out lowp vec3 frag_color;

void main() {
    frag_color = vec3(brightness, brightness / 3.0, brightness / 3.0);
    lowp float fog_blend = min(1.0, 1.1 - exp2(-fog_data.w * fog_level));
    frag_color = mix(frag_color, vec3(fog_data.x, fog_data.y, fog_data.z), fog_blend);
}