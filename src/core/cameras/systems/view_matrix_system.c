// todo: this should only update when either ScreenDimensions or FieldOfView changes
//      do a test function for this change perhaps
void ViewMatrixSystem(ecs_iter_t *it) {
    const Position3D *positions = ecs_field(it, Position3D, 1);
    const Rotation3D *rotations = ecs_field(it, Rotation3D, 2);
    const ProjectionMatrix *projectionMatrixs = ecs_field(it, ProjectionMatrix, 3);
    ViewMatrix *viewMatrixs = ecs_field(it, ViewMatrix, 4);
    // ecs_query_changed(it->query, &it, ScreenDimensions) || ecs_query_changed(q_read, &it, ScreenDimensions)
    for (int i = 0; i < it->count; i++) {
        const Position3D *position = &positions[i];
        const Rotation3D *rotation = &rotations[i];
        const ProjectionMatrix *projectionMatrix = &projectionMatrixs[i];
        ViewMatrix *viewMatrix = &viewMatrixs[i];
        float4x4 cameraPositionMatrix = float4x4_position(float3_multiply_float(position->value, -1.0f));
        float4x4 cameraViewMatrix = float4x4_multiply(cameraPositionMatrix, quaternion_to_matrix(rotation->value));
        viewMatrix->value = float4x4_multiply(cameraViewMatrix, projectionMatrix->value);
    }
}
zoxel_declare_system(ViewMatrixSystem)