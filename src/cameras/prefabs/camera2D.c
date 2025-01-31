ecs_entity_t prefab_camera2D_follower;

ecs_entity_t spawn_prefab_camera2D_follower(ecs_world_t *world, const ecs_entity_t prefab) {
    zox_prefab_child(prefab)
    // zox_prefab_name("prefab_camera2D")
    // ecs_add_id(world, e, EcsPrefab);
    zox_prefab_name("prefab_camera2D_follower")
    zox_add_tag(e, CameraFollower2D);
    zox_add(e, CameraTarget);
    prefab_camera2D_follower = e;
    return e;
}

ecs_entity_t spawn_camera2D_follower(ecs_world_t *world, float3 position, float4 rotation, int2 screenDimensions) {
    zox_instance(prefab_camera2D_follower)
    zox_name("camera2D_follower")
    zox_set(e, Position3D, { position })
    zox_set(e, Rotation3D, { rotation })
    zox_set(e, ScreenDimensions, { screenDimensions })
    return e;
}
