// Camera2D prefab
ecs_entity_t cameraPrefab;

void spawn_camera_prefab(ecs_world_t *world)
{
    ecs_entity_t e = ecs_new_w_pair(world, EcsIsA, baseCameraPrefab);
    ecs_add_id(world, e, EcsPrefab);
    ecs_set_name(world, e, "camera2D_prefab");
    zoxel_add_tag(world, e, CameraFollower2D);
    zoxel_add_component(world, e, CameraTarget);
    cameraPrefab = e;
}