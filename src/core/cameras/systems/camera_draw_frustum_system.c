extern void render_line3D(ecs_world_t *world, const float3 a, const float3 b, const color_rgb line_color);
float4x4 debug_view_projection_matrix;
float4x4 debug_transform_matrix;

void CameraDrawFrustumSystem(ecs_iter_t *it) {
    /*zox_iter_world()
    if (zox_cameras_disable_streaming) {
        draw_frustum_planes(world, debug_view_projection_matrix, debug_transform_matrix);
        return;
    }
    zox_field_in(TransformMatrix, transformMatrixs, 1)
    zox_field_in(ViewMatrix, viewMatrixs, 3)
    for (int i = 0; i < it->count; i++) {
        zox_field_i_in(ViewMatrix, viewMatrixs, viewMatrix)
        zox_field_i_in(TransformMatrix, transformMatrixs, transformMatrix)
        draw_frustum_planes(world, viewMatrix->value, transformMatrix->value);
        debug_view_projection_matrix = viewMatrix->value;
        debug_transform_matrix = transformMatrix->value;
    }*/
} zox_declare_system(CameraDrawFrustumSystem)

void FrustumDrawSystem(ecs_iter_t *it) {
    color_rgb debug_color = (color_rgb) { 0, 0, 0 };
    zox_iter_world()
    zox_field_in(FrustumCorners, frustumCornerss, 1)
    for (int i = 0; i < it->count; i++) {
        zox_field_i(FrustumCorners, frustumCornerss, frustumCorners)
        draw_frustum(world, frustumCorners->value, debug_color);
    }
} zox_declare_system(FrustumDrawSystem)
