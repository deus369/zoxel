void anchor_element_position2D_with_header(int2 *position, const float2 position_anchor, const int2 window_size, const float header_height) {
    // zox_log("   > header_height %f\n", header_height)
    position->x += (window_size.x / 2.0f) - window_size.x * position_anchor.x;
    position->y += (window_size.y / 2.0f) - (window_size.y + header_height) * position_anchor.y;
}

void reverse_anchor_element_position2D_with_header(int2 *position, const float2 position_anchor, const int2 window_size, const float header_height) {
    position->x -= (window_size.x / 2.0f) - window_size.x * position_anchor.x;
    position->y -= (window_size.y / 2.0f) - (window_size.y + header_height) * position_anchor.y;
}

void anchor_element_position2D(int2 *position, const float2 position_anchor, const int2 window_size) {
    position->x += (window_size.x / 2.0f) - window_size.x * position_anchor.x;
    position->y += (window_size.y / 2.0f) - window_size.y * position_anchor.y;
}

// #ifdef zoxel_on_android
//     if (anchor.y == 1) {
//         position->y -= android_header_size;
//     }
// #endif
/*if (anchor.x == 0) {
    position->x += window_size.x / 2.0f;
}
if (anchor.y == 0) {
    position->y += window_size.y / 2.0f;
}
if (anchor.x == 1) {
    position->x -= (window_size.x / 2.0f);
}
if (anchor.y == 1) {
    position->y -= (window_size.y / 2.0f) + header_height;
}*/


/*void anchor_element_pixel_position(int2 *position, const float2 position_anchor, const int2 window_size) {
    position->x += (window_size.x / 2.0f) - window_size.x * position_anchor.x;
    position->y += (window_size.y / 2.0f) - window_size.y * position_anchor.y;
}*/
