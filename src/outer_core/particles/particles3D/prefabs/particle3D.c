ecs_entity_t particle3D_prefab;

void spawn_prefab_particle3D(ecs_world_t *world) {
    ecs_defer_begin(world);
    ecs_entity_t e = ecs_new_prefab(world, "");
    set_unique_entity_name(world, e, "particle3D_prefab");
    zoxel_add_tag(world, e, Particle3D);
    // ecs_override(world, prefab, Particle2D);
    zoxel_set(world, e, Position3D, { { 0, 0, 0 } });
    zoxel_set(world, e, Rotation3D, { { 0, 0, 0, 1 } });
    zoxel_set(world, e, Scale1D, { 1 });
    // rendering
    zoxel_add(world, e, Brightness);
    // timing
    zoxel_add(world, e, DestroyInTime);
    #ifdef zoxel_physics
        zoxel_set(world, e, Velocity3D, { 0 });
        zoxel_set(world, e, Acceleration3D, { { 0, 0 } });
        // ecs_set(world, prefab, Torque, { 0 });
        // ecs_override(world, prefab, Torque);
    #endif
    ecs_defer_end(world);
    particle3D_prefab = e;
    #ifdef zoxel_debug_prefabs
        zoxel_log("spawn_prefab particle3D_prefab [%lu].\n", (long int) (e));
    #endif
}