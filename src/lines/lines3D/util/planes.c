void draw_planes(ecs_world_t *world, const plane *planes, const int plane_count) {
    // const float plane_size = 16;
    color_rgb plane_color = color_rgb_white;
    for (int i = 0; i < plane_count; i++) {
        if (i == 0) plane_color = (color_rgb) { 255, 0, 0 };
        else if (i == 1) plane_color = (color_rgb) { 0, 255, 0 };
        else if (i == 2) plane_color = (color_rgb) { 0, 0, 255 };
        else if (i == 3) plane_color = (color_rgb) { 55, 155, 255 };
        else if (i == 4) plane_color = (color_rgb) { 255, 255, 255 };
        else plane_color = (color_rgb) { 0, 0, 0 };
        float3 plane_point = float3_multiply_float(planes[i].normal, planes[i].distance);
        // float3 up = planes[i].normal;
        float3 up = (float3) { 0, 1, 0 }; // Assume an arbitrary up vector
        if (planes[i].normal.y == 1 || planes[i].normal.y == -1) up = (float3) { 1, 0, 0 };
        float3 right = float3_cross(up, planes[i].normal);
        float3 forward = float3_cross(planes[i].normal, right);
        float3 corners[4];
        corners[0] = float3_add(float3_add(plane_point, right), forward);
        corners[1] = float3_add(float3_subtract(plane_point, right), forward);
        corners[2] = float3_subtract(float3_subtract(plane_point, right), forward);
        corners[3] = float3_subtract(float3_add(plane_point, right), forward);
        render_line3D(world, corners[0], corners[1], plane_color);
        render_line3D(world, corners[1], corners[2], plane_color);
        render_line3D(world, corners[2], corners[3], plane_color);
        render_line3D(world, corners[3], corners[0], plane_color);
        // draw normal in middle of plane
        render_line3D_thickness(world, plane_point, float3_add(plane_point, planes[i].normal), plane_color, 16);
        render_line3D(world, float3_zero, plane_point, plane_color);
    }
}