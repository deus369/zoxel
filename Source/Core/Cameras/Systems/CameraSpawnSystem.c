//! Spawn a Camera
/**
 * Give the camera a Transform, a ViewMatrix.
 * Animate it moving a little upwards.
*/

ecs_entity_t cameraPrefab;
ecs_entity_t mainCamera;

void InitializeCameraSpawnSystem(ecs_world_t *world)
{
    cameraPrefab = ecs_new_prefab(world, "Camera");
    ecs_add(world, cameraPrefab, Camera);
    ecs_add(world, cameraPrefab, Position);
    ecs_add(world, cameraPrefab, Rotation);
    ecs_add(world, cameraPrefab, ViewMatrix);
    ecs_add(world, cameraPrefab, ScreenDimensions);
    ecs_add(world, cameraPrefab, FieldOfView);
}

ecs_entity_t SpawnCamera(ecs_world_t *world, float3 position, float4 rotation, int2 screenDimensions)
{
    ecs_entity_t newCamera = ecs_new_w_pair(world, EcsIsA, cameraPrefab);
    ecs_set(world, newCamera, Position, { 0, 0, 0 });
    ecs_set(world, newCamera, Rotation, { 0, 0, 0, 1 });
    ecs_set(world, newCamera, ViewMatrix, { malloc(16 * 4) });
    ecs_set(world, newCamera, ScreenDimensions, { screenDimensions.x, screenDimensions.y });
    ecs_set(world, newCamera, FieldOfView, { 60 });
    // this part will be hard
    // ecs_set(world, newCamera, ViewMatrix, { 0 });
    printf("Spawned Camera [%lu]\n", (long unsigned int) newCamera);
    mainCamera = newCamera;
    return newCamera;
}

void  DestroyMainCamera()
{
    ecs_delete(world, mainCamera);
}