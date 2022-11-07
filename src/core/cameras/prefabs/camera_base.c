// Camera2D prefab
ecs_entity_t baseCameraPrefab;

void spawn_camera_base_prefab(ecs_world_t *world)
{
    ecs_entity_t e = ecs_new_prefab(world, "Base_Camera_Prefab");
    zoxel_add_tag(world, e, Camera);
    zoxel_add_component(world, e, Position);
    zoxel_add_component(world, e, Rotation);
    zoxel_add_component(world, e, ProjectionMatrix);
    zoxel_add_component(world, e, ViewMatrix);
    zoxel_add_component(world, e, ScreenDimensions);
    zoxel_set_component(world, e, FieldOfView, { 60 });
    zoxel_set_component(world, e, FreeRoam, { 0 });
    zoxel_set_component(world, e, Euler, { { 0, 0, 0 } });
    baseCameraPrefab = e;
}