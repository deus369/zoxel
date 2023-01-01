//! Recalculates the View Matrix.
/**
 * This should only update when either ScreenDimensions or FieldOfView changes.
*/
void ViewMatrixSystem(ecs_iter_t *it)
{
    const Position *positions = ecs_field(it, Position, 1);
    const Rotation *rotations = ecs_field(it, Rotation, 2);
    const ProjectionMatrix *projectionMatrixs = ecs_field(it, ProjectionMatrix, 3);
    ViewMatrix *viewMatrixs = ecs_field(it, ViewMatrix, 4);
    // ecs_query_changed(it->query, &it, ScreenDimensions) || ecs_query_changed(q_read, &it, ScreenDimensions)
    for (int i = 0; i < it->count; i++)
    {
        const Position *position = &positions[i];
        const Rotation *rotation = &rotations[i];
        const ProjectionMatrix *projectionMatrix = &projectionMatrixs[i];
        ViewMatrix *viewMatrix = &viewMatrixs[i];
        // float4x4 cameraPositionMatrix = float4x4_view_matrix(position, (float3) { 0, 0, 1 }, (float3) { 0, 1, 0 } );
        float4x4 cameraPositionMatrix = float4x4_position(float3_multiply_float(position->value, -1.0f));
        float4x4 cameraViewMatrix = float4x4_multiply(cameraPositionMatrix, quaternion_to_matrix(rotation->value));
        viewMatrix->value = float4x4_multiply(cameraViewMatrix, projectionMatrix->value);
    }
}
zoxel_declare_system(ViewMatrixSystem)