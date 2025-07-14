in lowp vec2 uv;
uniform sampler2D tex;
uniform lowp float brightness;
uniform lowp float alpha;
out lowp vec4 color;

void main() {
    color = texture(tex, uv) * brightness;
    color.w *= alpha;
    if (alpha < -0.99) color.w = 1.0;
}