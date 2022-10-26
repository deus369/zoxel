#version 300 es

in lowp vec2 uv;
uniform lowp float brightness;
uniform sampler2D tex;
out lowp vec3 color;

void main()
{
    color = texture(tex, uv).xyz * brightness;
}

// color = vec3(0.0, 0.0, 0.0);
/*
if (isnan(color.x) || isnan(color.y) || isnan(color.z))
{
    color = vec3(1.0, 0.1, 0.1) * brightness;
}*/
// if (color.x <= 9999999.0 || color.y <= 9999999.0 || color.z <= 9999999.0)
// if (isPositive(color.x) || isPositive(color.y) || isPositive(color.z))
// {
//     color = vec3(0.3, 0.1, 0.2) * brightness;
// }
// else
// {
//     color = vec3(0.3, 0.1, 0.2) * brightness;
// }

// bool isNaN( float val )
// {
//   return ( val < 0.0 || 0.0 < val || val == 0.0 ) ? false : true;
// }

// bool isNegative( float val )
// {
//   return ( val < 0.0 ) ? false : true;
// }

// bool isPositive( float val )
// {
//   return ( val > 0.0 ) ? false : true;
// }

    /*
    mediump vec4 test = texture(tex, uv).rgba;
    if (test.x > 0.2)
    {
        color.x = 0.5;
        //color.y = 0.01;
        //color.z = 0.01;
    }*/

    // color = vec4(0.1, 0.1, 0.1, 0.0) * brightness;
    // color.w = 1.0;
    // color.y = uv.x;
    // color.z = uv.y;
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