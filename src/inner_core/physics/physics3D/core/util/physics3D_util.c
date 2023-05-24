void add_physics_debug(ecs_world_t *world, ecs_entity_t e) {
    zox_set_only(e, DebugCubeLines, { 1 })
    /*zox_add_tag(e, CubeLines)
    zox_set_only(e, CubeLinesThickness, { 4 })
    zox_set_only(e, ColorRGB, {{ 0, 255, 255 }})*/
}

void remove_physics_debug(ecs_world_t *world, ecs_entity_t e) {
    zox_set_only(e, DebugCubeLines, { 0 })
    /*zox_remove(e, CubeLines)
    zox_remove(e, CubeLinesThickness)
    zox_remove(e, ColorRGB)*/
}

void add_physics3D(ecs_world_t *world, ecs_entity_t e) {
    zox_set(e, InitializePhysics3D, { 0 })
    zox_add_tag(e, Frictioned)
    zox_set(e, Velocity3D, { { 0, 0, 0 } })
    zox_set(e, Acceleration3D, { { 0, 0, 0 } })
    zox_set(e, Omega3D, { quaternion_identity })
    zox_set(e, Alpha3D, { quaternion_identity })
    zox_set(e, Gravity3D, { { 0.0f, physics3D_gravity, 0.0f } })
    zox_set(e, Bounds3D, { { 0.5f, 0.5f, 0.5f } })
    // spawn lines around
    zox_add_tag(e, CubeLines)
    zox_set(e, CubeLinesThickness, { 4 })
    zox_set(e, ColorRGB, {{ 0, 255, 255 }})
    #ifdef zoxel_debug_bounds
        zox_set(e, DebugCubeLines, { 1 })
    #else
        zox_set(e, DebugCubeLines, { 0 })
    #endif
        // can i add children and then use observers to copy children accross??
        //  so the children get initialized too..?
        // zox_set(e, ColorRGB, {{ 255, 0, 0 }});
}