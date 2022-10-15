//! Spawn a Camera
/**
 * Give the camera a Transform, a ViewMatrix.
 * Animate it moving a little upwards.
*/

ecs_entity_t cameraPrefab;

void InitializeCameraSpawnSystem(ecs_world_t *world)
{
    cameraPrefab = ecs_new_prefab(world, "Camera");
    ecs_add(world, cameraPrefab, Camera);
    ecs_add(world, cameraPrefab, Position);
    ecs_add(world, cameraPrefab, Rotation);
    ecs_add(world, cameraPrefab, ViewMatrix);
}

void SpawnCamera(ecs_world_t *world, float3 position, float4 rotation)
{
    ecs_entity_t newCamera = ecs_new_w_pair(world, EcsIsA, cameraPrefab);
    ecs_set(world, newCamera, Position, { 0, 0, 0 });
    ecs_set(world, newCamera, Rotation, { 0, 0, 0, 1 });
    // this part will be hard
    // ecs_set(world, newCamera, ViewMatrix, { 0 });
    printf("Spawned Camera [%lu]\n", (long unsigned int) newCamera);
}