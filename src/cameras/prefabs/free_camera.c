// from now not needed... just change settings in base camera to remove any frame issues
// later to swap cameras ill probably need to switch them over a frame or something fancier
// as i need to control when it updates exactly
ecs_entity_t prefab_free_camera;

ecs_entity_t spawn_prefab_free_camera(ecs_world_t *world, const ecs_entity_t prefab) {
    zox_prefab_child(prefab)
    zox_prefab_name("prefab_free_camera")
    zox_prefab_set(e, CanRoam, { 0 })
    prefab_free_camera = e;
    return e;
}

ecs_entity_t spawn_free_camera(ecs_world_t *world, float3 position, float4 rotation, int2 screen_dimensions, int2 screen_position) {
    zox_instance(prefab_free_camera)
    zox_name("free_camera")
    zox_set(e, Position3D, { position })
    zox_set(e, Rotation3D, { rotation })
    zox_set(e, ScreenDimensions, { screen_dimensions })
    zox_set(e, ScreenPosition, { screen_position })
#ifndef zox_test_quaternion_camera
    zox_set(e, Euler, { quaternion_to_euler(rotation) })
    zox_add_tag(e, EulerOverride)
    zox_prefab_set(e, EulerLimitX, { { -camera_limit_x, camera_limit_x } }) // adds a limit, - half pi to + half pi, 0.8 is around half that
#endif
    return e;
}
