// Camera2D prefab
ecs_entity_t cameraPrefab;

void SpawnCameraPrefab(ecs_world_t *world)
{
    cameraPrefab = ecs_new_prefab(world, "Camera_Prefab");
    ecs_add(world, cameraPrefab, Camera);
    ecs_add(world, cameraPrefab, Position);
    ecs_add(world, cameraPrefab, Rotation);
    ecs_add(world, cameraPrefab, ViewMatrix);
    ecs_add(world, cameraPrefab, ScreenDimensions);
    ecs_add(world, cameraPrefab, FieldOfView);
    ecs_add(world, cameraPrefab, CameraFollower2D);
    ecs_add(world, cameraPrefab, CameraFree);
    ecs_override(world, cameraPrefab, CameraFree);
    ecs_set(world, cameraPrefab, CameraFree, { false });
    ecs_add(world, cameraPrefab, Euler);
    ecs_override(world, cameraPrefab, Euler);
    ecs_set(world, cameraPrefab, Euler, { { 0, 0, 0 } });
}