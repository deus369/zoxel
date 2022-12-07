#version 300 es

in lowp vec2 uv;
uniform lowp float brightness;
uniform sampler2D tex;
out lowp vec4 color;

void main()
{
    color = texture(tex, uv) * brightness;
    // color = vec4(uv.x, uv.y, 0.0, 1.0);
}