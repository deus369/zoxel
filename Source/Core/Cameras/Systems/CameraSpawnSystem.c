//! Spawn a Camera
/**
 * Give the camera a Transform, a ViewMatrix.
 * Animate it moving a little upwards.
*/

ecs_entity_t mainCamera;

ecs_entity_t SpawnCamera(ecs_world_t *world, float3 position, float4 rotation, int2 screenDimensions)
{
    ecs_entity_t newCamera = ecs_new_w_pair(world, EcsIsA, cameraPrefab);
    ecs_set(world, newCamera, Position, { position });
    ecs_set(world, newCamera, Rotation, { rotation });
    ecs_set(world, newCamera, ViewMatrix, { CreateZeroMatrix() });    // malloc(16 * 4)
    ecs_set(world, newCamera, ScreenDimensions, { { screenDimensions.x, screenDimensions.y } });
    ecs_set(world, newCamera, FieldOfView, { 60 });
    // this part will be hard
    // ecs_set(world, newCamera, ViewMatrix, { 0 });
    printf("Spawned Camera [%lu]\n", (long unsigned int) newCamera);
    mainCamera = newCamera;
    return newCamera;
}

//! Used for testing cleanup
void DestroyMainCamera()
{
    ecs_delete(world, mainCamera);
}