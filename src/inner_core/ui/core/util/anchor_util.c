void anchor_position2D(int2 *position, int2 window_size, float2 anchor, float header_height) {
    #ifdef zoxel_on_android
        if (anchor->y == 1) {
            position->y -= android_header_size;
        }
    #endif
    if (anchor.x == 0) {
        position->x += window_size.x / 2.0f;
    }
    if (anchor.y == 0) {
        position->y += window_size.y / 2.0f;
    }
    if (anchor.x == 1.0f) {
        position->x -= (window_size.x / 2.0f);
    }
    if (anchor.y == 1.0f) {
        position->y -= (window_size.y / 2.0f) + header_height;
    }
}