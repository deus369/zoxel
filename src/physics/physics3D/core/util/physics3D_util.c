void add_physics_debug(ecs_world_t *world, const ecs_entity_t e) {
    zox_set(e, DebugCubeLines, { 1 })
    /*zox_add_tag(e, CubeLines)
    zox_set(e, CubeLinesThickness, { 4 })
    zox_set(e, ColorRGB, {{ 0, 255, 255 }})*/
}

void remove_physics_debug(ecs_world_t *world, const ecs_entity_t e) {
    zox_set(e, DebugCubeLines, { 0 })
    /*zox_remove(e, CubeLines)
    zox_remove(e, CubeLinesThickness)
    zox_remove(e, ColorRGB)*/
}

void add_physics3D(ecs_world_t *world, const ecs_entity_t e) {
    zox_add_tag(e, Frictioned)
    zox_prefab_set(e, LastPosition3D, { float3_zero })
    zox_prefab_set(e, InitializePhysics3D, { 0 })
    zox_prefab_set(e, Velocity3D, { { 0, 0, 0 } })
    zox_prefab_set(e, Acceleration3D, { { 0, 0, 0 } })
    zox_prefab_set(e, Omega3D, { quaternion_identity })
    zox_prefab_set(e, Alpha3D, { quaternion_identity })
    zox_prefab_set(e, Gravity3D, { { 0.0f, physics3D_gravity, 0.0f } })
    zox_prefab_set(e, Bounds3D, { { 0.5f, 0.5f, 0.5f } })
    zox_prefab_set(e, Grounded, { 0 })
    zox_prefab_set(e, Jump, { 0 })
#ifdef zoxel_debug_bounds
    prefab_add_cube_lines(world, e, color_rgb_white, 1);
#else
    prefab_add_cube_lines(world, e, color_rgb_white, 0);
#endif
}

unsigned char can_jump(ecs_world_t *world, const ecs_entity_t e) {
    return !zox_gett_value(e, DisableMovement) && zox_gett_value(e, Grounded);
}
