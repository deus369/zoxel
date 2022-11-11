// Camera2D prefab
ecs_entity_t base_camera_prefab;

void spawn_camera_base_prefab(ecs_world_t *world)
{
    ecs_entity_t e = ecs_new_prefab(world, "base_camera_prefab");
    zoxel_add_tag(world, e, Camera);
    zoxel_add_component(world, e, Position);
    zoxel_add_component(world, e, Rotation);
    zoxel_set_component(world, e, Euler, { { 0, 0, 0 } });
    zoxel_add_component(world, e, ProjectionMatrix);
    zoxel_add_component(world, e, ViewMatrix);
    zoxel_add_component(world, e, ScreenDimensions);
    zoxel_add_component(world, e, FieldOfView);
    base_camera_prefab = e;
}