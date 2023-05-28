ecs_entity_t particle3D_prefab;

void spawn_prefab_particle3D(ecs_world_t *world) {
    ecs_defer_begin(world);
    zox_prefab()
    zox_name("prefab_particle3D")
    zox_add_tag(e, Particle3D)
    // ecs_override(world, prefab, Particle2D)
    zox_set(e, Position3D, { float3_zero })
    zox_set(e, Rotation3D, { quaternion_identity })
    zox_set(e, Scale1D, { 1 })
    zox_add(e, Brightness)
    zox_add(e, DestroyInTime)
    #ifdef zoxel_physics
        zox_set(e, Velocity3D, { float3_zero })
        zox_set(e, Acceleration3D, { float3_zero })
        // ecs_set(world, prefab, Torque, { 0 })
        // ecs_override(world, prefab, Torque)
    #endif
    ecs_defer_end(world);
    particle3D_prefab = e;
    #ifdef zoxel_debug_prefabs
        zoxel_log("spawn_prefab particle3D_prefab [%lu].\n", (long int) (e));
    #endif
}