void add_physics3D(ecs_world_t *world, ecs_entity_t e) {
    zoxel_set(world, e, InitializePhysics3D, { 0 });
    zoxel_add_tag(world, e, Frictioned);
    zoxel_set(world, e, Velocity3D, { { 0, 0, 0 } });
    zoxel_set(world, e, Acceleration3D, { { 0, 0, 0 } });
    zoxel_set(world, e, Omega3D, { quaternion_identity });
    zoxel_set(world, e, Alpha3D, { quaternion_identity });
    zoxel_set(world, e, Gravity3D, { { 0.0f, physics3D_gravity, 0.0f } });
    zoxel_set(world, e, Bounds3D, { { 0.5f, 0.5f, 0.5f } });
    // spawn lines around
    #ifdef zoxel_debug_bounds
        // can i add children and then use observers to copy children accross??
        //  so the children get initialized too..?
        zoxel_add_tag(world, e, CubeLines);
        zoxel_set(world, e, CubeLinesThickness, { 4 });
        zoxel_set(world, e, ColorRGB, {{ 0, 255, 255 }});
        // zoxel_set(world, e, ColorRGB, {{ 255, 0, 0 }});
    #endif
}

/*void add_physics3D2(ecs_world_t *world, ecs_entity_t e) {
    add_physics3D(world, e);
    float bound_value = 8.0f;
    zoxel_set(world, e, Bounds3D, { { bound_value, bound_value, bound_value } });
    // zoxel_set(world, e, Torque3D, { { 0, 0, 0, 0 } });
}*/