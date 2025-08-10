// rename screen to viewport
int2 screen_to_canvas_size(const int2 size, const float4 screen_to_canvas) {
    return (int2) { screen_to_canvas.x * size.x, screen_to_canvas.y * size. y };
}

// rename screen to viewport
int2 screen_to_canvas_position(const int2 size, const float4 screen_to_canvas) {
    return (int2) { screen_to_canvas.z * size.x, screen_to_canvas.w * size. y };
}