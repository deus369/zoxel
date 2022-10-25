#version 300 es

// layout (location = 0)
in lowp vec2 uv;
uniform lowp float brightness;
uniform sampler2D tex;
out lowp vec4 color;

void main()
{
    // color = vec4(1.0, 0.25, 0.15, 0) * brightness;
    // color = vec4(0.1, 0.1, 0.1, 0.0) * brightness;
    // color.w = 1.0;
    // color.y = uv.x;
    // color.z = uv.y;
    color = texture(tex, uv).rgba * brightness;
    // if(gl_FrontFacing) 	color = texture(tex, uv).rgba; 	else discard;
    // lowp vec4 color2 = texture(tex, uv).rgba * brightness;
    // color.x = color2.x;
    // color.y = color2.y;
    // color.z = color2.z;
    // color = vec4(color2.x + 0.1, color2.y, color2.z, 255.0);
    // color.w = 1.0;
    // color = vec4(1.0, 1.0, 0.5, 1.0);
    // color = vec4(uvOutput.x, uvOutput.y, 0, 1) * brightness;
    /*lowp vec3 color2 = vec3(0.0, 0.0, 0.0);
    if (uvOutput.x != 0.0)
    {
        color2.y = 1.0;
    }
    if (uvOutput.y != 0.0)
    {
        color2.z = 1.0;
    }
    color = vec4(1.0, 0.1 + color2.y, 0.05 + color2.z, 0) * brightness;*/
}