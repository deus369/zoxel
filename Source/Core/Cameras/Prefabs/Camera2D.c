// Camera2D prefab
ecs_entity_t cameraPrefab;

void SpawnCameraPrefab(ecs_world_t *world)
{
    cameraPrefab = ecs_new_prefab(world, "Camera");
    ecs_add(world, cameraPrefab, Camera);
    ecs_add(world, cameraPrefab, Position);
    ecs_add(world, cameraPrefab, Rotation);
    ecs_add(world, cameraPrefab, ViewMatrix);
    ecs_add(world, cameraPrefab, ScreenDimensions);
    ecs_add(world, cameraPrefab, FieldOfView);
}