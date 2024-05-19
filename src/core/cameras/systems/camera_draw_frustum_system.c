extern void render_line3D(ecs_world_t *world, const float3 a, const float3 b, const color_rgb line_color);
float4x4 debug_view_projection_matrix;
float4x4 debug_transform_matrix;

void CameraDrawFrustumSystem(ecs_iter_t *it) {
    zox_iter_world()
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
    }
} zox_declare_system(CameraDrawFrustumSystem)

//
//zox_field_in(ProjectionMatrix, projectionMatrixs, 2)
//
//zox_field_i_in(ProjectionMatrix, projectionMatrixs, projectionMatrix)
// draw_frustum_planes(world, projectionMatrix->value, transformMatrix->value);
//zox_field_i_in(Position3D, position3Ds, position3D)
//zox_field_i_in(Rotation3D, rotation3Ds, rotation3D)
//zox_field_i_in(CameraPlanes, cameraPlaness, cameraPlanes)
/*render_line3D(position3D->value, float3_add(position3D->value, float4_rotate_float3(rotation3D->value, (float3) { 0, 0, line_length } )), line_color);
float3* corners = find_plane_corners(cameraPlanes->value);
for (int j = 0; j < 8; j++) {
    float3 point_a = corners[j];
    float3 point_b = corners[(j + 1) % 8];
    render_line3D(point_a, point_b, line_color);
    // zox_log("point %i: %fx%fx%f\n", j, point_a.x, point_a.y, point_a.z)
}
free(corners);*/
