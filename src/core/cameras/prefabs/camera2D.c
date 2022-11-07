// Camera2D prefab
ecs_entity_t cameraPrefab;

void spawn_camera_prefab(ecs_world_t *world)
{
    cameraPrefab = ecs_new_w_pair(world, EcsIsA, baseCameraPrefab);
    ecs_add_id(world, cameraPrefab, EcsPrefab);
    ecs_set_name(world, cameraPrefab, "camera2D_prefab");
    zoxel_add_tag(world, cameraPrefab, CameraFollower2D);
}