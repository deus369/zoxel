uniform lowp float brightness;
uniform lowp vec3 sky_top_color;
uniform lowp vec3 sky_bottom_color;
uniform lowp float time;
uniform lowp vec4 fog_data;
in lowp vec3 mesh_pos;
in highp float fog_level;
out lowp vec3 frag_color;

lowp float rand(lowp vec2 co) {
    return fract(sin(dot(co, vec2(12.9898,78.233))) * 43758.5453);
}

lowp vec3 sky_gradient(lowp vec3 color) {
    if (mesh_pos.y > 0.1) {
        lowp float height_power = (mesh_pos.y - 0.1) * (1.0 - abs(max(mesh_pos.x, mesh_pos.z))) * 1.1;
        color.x += height_power;
        color.y += height_power;
        color.z += height_power;
        if (mesh_pos.x >= -0.1 && mesh_pos.x <= 0.1 && mesh_pos.z >= -0.1 && mesh_pos.z <= 0.1) {
            lowp float to_mid_power = (1.0 - 10.0 * max(abs(mesh_pos.x), abs(mesh_pos.z)));
            color.x += to_mid_power;
            color.y += to_mid_power;
            color.z += to_mid_power;
            lowp float noise2 = rand(time * mesh_pos.xy);
            color -= vec3(noise2) * 1.4;
        }
    }
    return color;
}

void main() {
    lowp vec3 sky_top_color2 = sky_top_color;
    lowp float gradient = clamp((mesh_pos.y + 0.0) * 1.0, 0.0, 1.0);
    frag_color = vec3(mix(sky_bottom_color, sky_top_color2, gradient)) * brightness;
    frag_color = sky_gradient(frag_color);
    frag_color -= vec3(1) * 0.05;
    lowp float noise = rand(time * mesh_pos.xy);
    frag_color += vec3(noise) * 0.1;
}