// Camera2D prefab
ecs_entity_t base_camera_prefab;

void spawn_camera_base_prefab(ecs_world_t *world)
{
    ecs_defer_begin(world);
    ecs_entity_t e = ecs_new_prefab(world, "base_camera_prefab");
    #ifdef zoxel_debug_prefabs
    printf("spawn_prefab camera_base [%lu].\n", (long int) (e));
    #endif
    zoxel_add_tag(world, e, Camera);
    zoxel_add(world, e, Position);
    zoxel_add(world, e, Rotation);
    zoxel_set(world, e, Euler, { { 0, 0, 0 } });
    zoxel_add(world, e, ProjectionMatrix);
    zoxel_add(world, e, ViewMatrix);
    zoxel_add(world, e, ScreenDimensions);
    zoxel_add(world, e, FieldOfView);
    base_camera_prefab = e;
    ecs_defer_end(world);
}