void add_physics3D(ecs_world_t *world, ecs_entity_t e) {
    zox_set(e, InitializePhysics3D, { 0 });
    zox_add_tag(e, Frictioned);
    zox_set(e, Velocity3D, { { 0, 0, 0 } });
    zox_set(e, Acceleration3D, { { 0, 0, 0 } });
    zox_set(e, Omega3D, { quaternion_identity });
    zox_set(e, Alpha3D, { quaternion_identity });
    zox_set(e, Gravity3D, { { 0.0f, physics3D_gravity, 0.0f } });
    zox_set(e, Bounds3D, { { 0.5f, 0.5f, 0.5f } });
    // spawn lines around
    #ifdef zoxel_debug_bounds
        // can i add children and then use observers to copy children accross??
        //  so the children get initialized too..?
        zox_add_tag(e, CubeLines);
        zox_set(e, CubeLinesThickness, { 4 });
        zox_set(e, ColorRGB, {{ 0, 255, 255 }});
        // zox_set(e, ColorRGB, {{ 255, 0, 0 }});
    #endif
}

/*void add_physics3D2(ecs_world_t *world, ecs_entity_t e) {
    add_physics3D(world, e);
    float bound_value = 8.0f;
    zox_set(e, Bounds3D, { { bound_value, bound_value, bound_value } });
    // zox_set(e, Torque3D, { { 0, 0, 0, 0 } });
}*/