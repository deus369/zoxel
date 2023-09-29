ecs_entity_t prefab_particle3D;

ecs_entity_t spawn_prefab_particle3D(ecs_world_t *world) {
    zox_prefab()
    zox_prefab_name("prefab_particle3D")
    zox_add_tag(e, Particle3D)
    // ecs_override(world, prefab, Particle2D)
    zox_prefab_set(e, Position3D, { float3_zero })
    zox_prefab_set(e, Rotation3D, { quaternion_identity })
    zox_prefab_set(e, Scale1D, { 1 })
    zox_prefab_set(e, Velocity3D, { float3_zero })
    zox_prefab_set(e, Acceleration3D, { float3_zero })
    // ecs_override(world, prefab, Torque)
    zox_prefab_set(e, Brightness, { 1 })
    zox_prefab_set(e, DestroyInTime, { 3 })
    prefab_particle3D = e;
    #ifdef zoxel_debug_prefabs
        zox_log("spawn_prefab particle3D [%lu]\n", e)
    #endif
    return e;
}

ecs_entity_t spawn_particle3D(ecs_world_t *world, float3 position3D, float3 acceleration3D) {
    zox_instance(prefab_particle3D)
    zox_name("particle3D")
    zox_prefab_set(e, Position3D, { position3D })
    zox_prefab_set(e, Acceleration3D, { acceleration3D })
    // zox_prefab_set(e, Velocity3D, { velocity3D })
    return e;
}