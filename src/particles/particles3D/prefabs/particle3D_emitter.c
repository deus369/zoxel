ecs_entity_t spawn_prefab_particle3D_emitter(ecs_world_t *world) {
    zox_prefab()
    zox_prefab_name("particle3D_emitter")
    zox_add_tag(e, Particle3DEmitter)
    zox_prefab_set(e, ParticleEmitRate, { 0 })
    // attach to parent character
    zox_prefab_set(e, Position3D, { float3_zero })
    zox_prefab_set(e, Rotation3D, { quaternion_identity })
    zox_prefab_set(e, Scale1D, { 1 })
    zox_prefab_set(e, LocalPosition3D, { float3_zero })
    zox_prefab_set(e, LocalRotation3D, { quaternion_identity })
    zox_prefab_set(e, ParentLink, { 0 })
    zox_prefab_set(e, Bounds3D, { 0 })
    zox_prefab_set(e, Color, { color_white })
    return e;
}

ecs_entity_t spawn_particle3D_emitter(ecs_world_t *world, const ecs_entity_t parent, const int emit_rate, const float3 bounds, const color particles_color) {
    zox_instance(prefab_particle3D_emitter)
    zox_name("particle3D_emitter")
    zox_set(e, ParentLink, { parent })
    zox_set(e, ParticleEmitRate, { emit_rate })
    zox_set(e, Bounds3D, { bounds })
    zox_set(e, Color, { particles_color })
    return e;
}
