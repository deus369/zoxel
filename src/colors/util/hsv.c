float color_to_hue(const color value) {
    const float red = (int) value.r / 255.0f;
    const float green = (int) value.g / 255.0f;
    const float blue = (int) value.b / 255.0f;
    const float max = float_max(red, float_max(green, blue));
    const float min = float_min(red, float_min(green, blue));
    const float delta = (max - min);
    int multi = 60; // 42; // 60
    float hue = 0; // (int) ceil
    if (red == max) hue = (multi * ((green - blue) / delta)); //  % 6;
    else if (green == max) hue = (multi * ((int) 2 + ((blue - red) / delta)));
    else hue = (multi * ((int) 4 + ((red - green) / delta)));
    if (hue < 0) hue = 360 + hue;
    return hue;
}

float color_to_saturation(const color value) {
    const float red = (int) value.r / 255.0f;
    const float green = (int) value.g / 255.0f;
    const float blue = (int) value.b / 255.0f;
    const float max = float_max(red, float_max(green, blue));
    const float min = float_min(red, float_min(green, blue));
    const float delta = (max - min);
    if (max == 0) return 0;
    else return 100.0f * (delta / max);
}

float color_to_value(const color value) {
    const float red = (int) value.r / 255.0f;
    const float green = (int) value.g / 255.0f;
    const float blue = (int) value.b / 255.0f;
    const float max = float_max(red, float_max(green, blue));
    return max * 100;
}

float3 color_to_hsv(const color value) {
    return (float3) {
        color_to_hue(value),
        color_to_saturation(value),
        color_to_value(value)
    };
}
// hsv is 0 to 360, 0 to 100, 0 to 100, hue, saturation and value
color hsv_to_color(const float3 hsv) {
    const float hue = hsv.x;
    const float saturation = hsv.y / 100.0f;
    const float value = hsv.z / 100.0f;
    float chroma = value * saturation;
    float hue_ = zox_fmod(hue / 60.0f, 6.0f);
    float x = chroma * (1 - fabs(zox_fmod(hue_, 2.0f) - 1));
    float r, g, b;
    if (hue_ >= 0 && hue_ < 1) {
        r = chroma;
        g = x;
        b = 0;
    } else if (hue_ >= 1 && hue_ < 2) {
        r = x;
        g = chroma;
        b = 0;
    } else if (hue_ >= 2 && hue_ < 3) {
        r = 0;
        g = chroma;
        b = x;
    } else if (hue_ >= 3 && hue_ < 4) {
        r = 0;
        g = x;
        b = chroma;
    } else if (hue_ >= 4 && hue_ < 5) {
        r = x;
        g = 0;
        b = chroma;
    } else {
        r = chroma;
        g = 0;
        b = x;
    }
    float m = value - chroma;
    r += m;
    g += m;
    b += m;
    r = ceil(r * 255);
    g = ceil(g * 255);
    b = ceil(b * 255);
    return (color) { (byte) r, (byte) g, (byte) b, 255 };
}

float3 generate_hsv_v_s(
    const float2 hue_limits,
    const float2 value_limits,
    const float2 saturation_limits
) {
    return (float3) {
        hue_limits.x + (hue_limits.y - hue_limits.x) * (rand() % 100) * 0.01f,
        saturation_limits.x + (saturation_limits.y - saturation_limits.x) * (rand() % 100) * 0.01f,
        value_limits.x + (value_limits.y - value_limits.x) * (rand() % 100) * 0.01f };
}

// Depending on what RGB color channel is the max value. The three different formulas are:
// If Red is max, then Hue = (green-blue)/(max-min)
// If Green is max, then Hue = 2.0 + (blue-red)/(max-min)
// If Blue is max, then Hue = 4.0 + (red-green)/(max-min)
