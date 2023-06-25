ecs_entity_t prefab_free_camera;

ecs_entity_t spawn_prefab_free_camera(ecs_world_t *world) {
    ecs_defer_begin(world);
    zox_prefab_child(prefab_base_camera)
    zox_set(e, FreeRoam, { 0 })
    ecs_defer_end(world);
    prefab_free_camera = e;
    #ifdef zoxel_debug_prefabs
        zoxel_log("spawn_prefab free_camera [%lu].\n", (long int) (e));
    #endif
    return e;
}

ecs_entity_t spawn_free_camera(ecs_world_t *world, float3 position, float4 rotation,
    int2 screen_dimensions, int2 screen_position) {
    ecs_defer_begin(world);
    zox_instance(prefab_free_camera)
    zox_name("free_camera")
    zox_set_only(e, Position3D, { position })
    zox_set_only(e, Rotation3D, { rotation })
    zox_set_only(e, ScreenDimensions, { screen_dimensions })
    zox_set_only(e, ScreenPosition, { screen_position })
    #ifndef zox_test_quaternion_camera
        zox_set_only(e, Euler, { quaternion_to_euler(rotation) })
        zox_add_tag(e, EulerOverride)
        zox_set(e, EulerLimitX, { { -camera_limit_x, camera_limit_x } }) // adds a limit, - half pi to + half pi, 0.8 is around half that
    #endif
    ecs_defer_end(world);
    #ifdef zoxel_debug_spawns
        zoxel_log("Spawned Free Camera [%lu]\n", (long int) e);
    #endif
    return e;
}