// Camera2D prefab
ecs_entity_t camera2D_follower_prefab;

void spawn_camera2D_follower_prefab(ecs_world_t *world) {
    ecs_defer_begin(world);
    // ecs_entity_t e = ecs_new_w_pair(world, EcsIsA, prefab_base_camera);
    zox_prefab_child(prefab_base_camera)
    ecs_add_id(world, e, EcsPrefab);
    zox_name("prefab_camera2D_follower")
    zox_add_tag(e, CameraFollower2D);
    zox_add(e, CameraTarget);
    ecs_defer_end(world);
    camera2D_follower_prefab = e;
    #ifdef zoxel_debug_prefabs
        zoxel_log("spawn_prefab camera2D [%lu].\n", (long int) (e));
    #endif
}

ecs_entity_t spawn_camera2D_follower(ecs_world_t *world, float3 position, float4 rotation, int2 screenDimensions) {
    zox_instance(camera2D_follower_prefab)
    zox_name("camera2D_follower")
    ecs_set(world, e, Position3D, { position });
    ecs_set(world, e, Rotation3D, { rotation });
    ecs_set(world, e, ScreenDimensions, { screenDimensions });
    // zoxel_log("Spawned Camera [%lu]\n", (long unsigned int) e);
    return e;
}