extern void render_line3D(ecs_world_t *world, const float3 a, const float3 b, const color_rgb line_color);
extern void render_line3D_thickness(ecs_world_t *world, const float3 a, const float3 b, const color_rgb line_color, const float thickness);

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
        corners[1] = float3_add(float3_sub(plane_point, right), forward);
        corners[2] = float3_sub(float3_sub(plane_point, right), forward);
        corners[3] = float3_sub(float3_add(plane_point, right), forward);
        render_line3D(world, corners[0], corners[1], plane_color);
        render_line3D(world, corners[1], corners[2], plane_color);
        render_line3D(world, corners[2], corners[3], plane_color);
        render_line3D(world, corners[3], corners[0], plane_color);
        // draw normal in middle of plane
        render_line3D_thickness(world, plane_point, float3_add(plane_point, planes[i].normal), plane_color, 16);
        render_line3D(world, float3_zero, plane_point, plane_color);
    }
}

void draw_frustum(ecs_world_t *world, float3 *frustum, const color_rgb debug_color) {
    // const color_rgb plane_color = (color_rgb) { 255, 125, 55 };
    const color_rgb near_plane_color = debug_color; // (color_rgb) { 255, 22, 22 };
    const color_rgb far_plane_color = debug_color; // (color_rgb) { 205, 22, 22 };
    const color_rgb side_color = debug_color; // (color_rgb) { 233, 55, 55 };
    // draw near plane
    render_line3D(world, frustum[0], frustum[1], near_plane_color);
    render_line3D(world, frustum[1], frustum[2], near_plane_color);
    render_line3D(world, frustum[2], frustum[3], near_plane_color);
    render_line3D(world, frustum[3], frustum[0], near_plane_color);
    // draw far plane
    render_line3D(world, frustum[4], frustum[5], far_plane_color);
    render_line3D(world, frustum[5], frustum[6], far_plane_color);
    render_line3D(world, frustum[6], frustum[7], far_plane_color);
    render_line3D(world, frustum[7], frustum[4], far_plane_color);
    // draw far plane
    render_line3D(world, frustum[0], frustum[4], side_color);
    render_line3D(world, frustum[1], frustum[5], side_color);
    render_line3D(world, frustum[2], frustum[6], side_color);
    render_line3D(world, frustum[3], frustum[7], side_color);
}

/*void draw_frustum_planes(ecs_world_t *world, const float4x4 view_projection_matrix, const float4x4 transform_matrix) {
    // float3 *frustum = calculate_frustum_corners(view_projection_matrix);
#if defined(zox_test_frustum)
    plane *planes = create_test_planes_position(debug_plane_position, debug_plane_distance);
#elif defined(zox_test_frustum2)
    plane *planes = create_test_planes_position((float3) { transform_matrix.w.x, transform_matrix.w.y, transform_matrix.w.z }, debug_plane_distance);
#else
    plane *planes = malloc(6 * sizeof(plane));
    calculate_planes_from_frustum(frustum, planes);
#endif
    // draw_frustum(world, frustum);
    draw_planes(world, planes, 6);
    free(planes);
    // free(frustum);
}*/

/*void draw_frustum_planes_old(ecs_world_t *world, const float4x4 projection_matrix, const float4x4 transform_matrix) {
    float3 *frustum = calculate_frustum_corners_old(projection_matrix, transform_matrix);
#if defined(zox_test_frustum)
    plane *planes = create_test_planes_position(debug_plane_position, debug_plane_distance);
#elif defined(zox_test_frustum2)
    plane *planes = create_test_planes_position((float3) { transform_matrix.w.x, transform_matrix.w.y, transform_matrix.w.z }, 16);
#else
    plane *planes = malloc(6 * sizeof(plane));
    calculate_planes_from_frustum(frustum, planes);
#endif
    draw_frustum(world, frustum);
    draw_planes(world, planes, 6);
    free(planes);
    free(frustum);
}*/

int get_label_camera(ecs_world_t *world, const ecs_entity_t player, char buffer[], int buffer_size, int buffer_index) {
    const ecs_entity_t camera = zox_get_value(player, CameraLink)
    if (!camera) return buffer_index;
    const float3 position3D = zox_get_value(camera, Position3D)
    const float4 rotation3D = zox_get_value(camera, Rotation3D)
    const float3 euler = quaternion_to_euler_360(rotation3D);
    buffer_index += snprintf(buffer + buffer_index, buffer_size - buffer_index, "camera_pos [%ix%ix%i]\n", (int) position3D.x, (int) position3D.y, (int) position3D.z);
    buffer_index += snprintf(buffer + buffer_index, buffer_size - buffer_index, "camera_rot [%ix%ix%i]\n", (int) euler.x, (int) euler.y, (int) euler.z);
    return buffer_index;
}

int get_label_camera_planes(ecs_world_t *world, const ecs_entity_t player, char buffer[], int buffer_size, int buffer_index) {
    const ecs_entity_t camera = zox_get_value(player, CameraLink)
    if (!camera || !zox_has(camera, CameraPlanes)) return buffer_index;
    // const float6 bounds = zox_get_value(camera, Position3DBounds)
    // buffer_index += snprintf(buffer + buffer_index, buffer_size - buffer_index, "camera bounds x[%.0f:%.0f] y[%.0f:%.0f] z[%.0f:%.0f]\n", bounds.x, bounds.y, bounds.z, bounds.w, bounds.u, bounds.v);
    const CameraPlanes *planes = zox_get(camera, CameraPlanes)
    if (planes->length != 6) buffer_index += snprintf(buffer + buffer_index, buffer_size - buffer_index, "camera_planes invalid!\n");
    else {
        buffer_index += snprintf(buffer + buffer_index, buffer_size - buffer_index, "frustum planes [6]\n");
        for (int i = 0; i < 6; i++) buffer_index += snprintf(buffer + buffer_index, buffer_size - buffer_index, "%i [%.1fx%.1fx%.1f] [%.1f]\n", (i + 1), planes->value[i].normal.x, planes->value[i].normal.y,  planes->value[i].normal.z, planes->value[i].distance);
    }
    return buffer_index;
}


int get_label_camera_frustum(ecs_world_t *world, const ecs_entity_t player, char buffer[], int buffer_size, int buffer_index) {
    const ecs_entity_t camera = zox_get_value(player, CameraLink)
    if (!camera || !zox_has(camera, FrustumCorners)){
         buffer_index += snprintf(buffer + buffer_index, buffer_size - buffer_index, "invalid camera\n");
        return buffer_index;
    }
    const FrustumCorners *corners = zox_get(camera, FrustumCorners)
    if (corners->length != 8) {
        buffer_index += snprintf(buffer + buffer_index, buffer_size - buffer_index, "frustum corners invalid!\n");
    } else {
        buffer_index += snprintf(buffer + buffer_index, buffer_size - buffer_index, "frustum corners [8]\n");
        for (int i = 0; i < 8; i++) {
            buffer_index += snprintf(buffer + buffer_index, buffer_size - buffer_index, "%i [%.1fx%.1fx%.1f]\n", (i + 1), corners->value[i].x, corners->value[i].y,  corners->value[i].z);
        }
    }
    return buffer_index;
}
