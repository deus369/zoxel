entity prefab_camera2D_follower;

entity spawn_prefab_camera2D_follower(ecs *world, const entity prefab) {
    zox_prefab_child(prefab)
    // zox_prefab_name("camera2D")
    // ecs_add_id(world, e, EcsPrefab);
    zox_prefab_name("camera2D_follower")
    zox_add_tag(e, CameraFollower2);
    zox_prefab_add(e, CameraTarget);
    prefab_camera2D_follower = e;
    return e;
}

entity spawn_camera2D_follower(ecs *world, float3 position, float4 rotation, int2 screenDimensions) {
    zox_instance(prefab_camera2D_follower)
    zox_name("camera2D_follower")
    zox_set(e, Position3D, { position })
    zox_set(e, Rotation3D, { rotation })
    zox_set(e, ScreenDimensions, { screenDimensions })
    return e;
}
