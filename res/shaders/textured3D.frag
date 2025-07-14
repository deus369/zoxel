in lowp vec3 vertex_color_frag;
in lowp vec2 uv;
in highp float fog_level;
uniform sampler2D tex;
uniform lowp vec4 fog_data;
uniform lowp float brightness;
out lowp vec4 frag_color;

void main() {
    lowp vec4 texture_color = texture(tex, uv);
    if (texture_color.a <= 0.0) {
        discard;
    }
    lowp vec3 mix_color = texture_color.xyz * vertex_color_frag * brightness;
    lowp float fog_blend = min(1.0, 1.1 - exp2(-fog_data.w * fog_level));
    mix_color = mix(mix_color, vec3(fog_data.x, fog_data.y, fog_data.z), fog_blend);
    frag_color = vec4(mix_color, texture_color.w);
}