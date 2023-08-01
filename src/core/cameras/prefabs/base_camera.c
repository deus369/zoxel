ecs_entity_t prefab_base_camera;

ecs_entity_t spawn_camera_base_prefab(ecs_world_t *world) {
    ecs_defer_begin(world);
    zox_prefab()
    zox_name("prefab_base_camera")
    zox_add_tag(e, Camera)
    zox_add(e, Position3D)
    zox_add(e, Rotation3D)
    zox_set(e, ParentLink, { 0 })
    zox_add(e, LocalPosition3D)
    zox_set(e, LocalRotation3D, { quaternion_identity })
    zox_set(e, Euler, { { 0, 0, 0 } })
    zox_set(e, ProjectionMatrix, { float4x4_identity() })
    zox_set(e, ViewMatrix, { float4x4_identity() })
    zox_set(e, ScreenDimensions, { { 0, 0 } })
    zox_set(e, ScreenPosition, { { 0, 0 } })
    zox_set(e, FieldOfView, { camera_fov })
    zox_set(e, CameraNearDistance, { 0.01f })
    zox_set(e, CanFreeRoam, { 0 })
    zox_set(e, FreeRoam, { 0 }) // newer
    ecs_defer_end(world);
    prefab_base_camera = e;
    #ifdef zoxel_debug_prefabs
        zoxel_log(" + spawned prefab camera_base [%lu].\n", (long int) (e));
    #endif
    return e;
}

ecs_entity_t spawn_base_camera(ecs_world_t *world, float3 position, float4 rotation, int2 screen_dimensions, int2 screen_position) {
    ecs_defer_begin(world);
    zox_instance(prefab_base_camera)
    zox_name("base_camera")
    zox_set_only(e, Position3D, { position })
    zox_set_only(e, Rotation3D, { rotation })
    zox_set_only(e, ScreenDimensions, { screen_dimensions })
    zox_set_only(e, ScreenPosition, { screen_position })
    ecs_defer_end(world);
    #ifdef zoxel_debug_spawns
        zoxel_log(" + spawned base camera [%lu]\n", (long int) e);
    #endif
    return e;
}