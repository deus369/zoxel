void Particle3DEmitSystem(ecs_iter_t *it) {
    zox_sys_world()
    zox_sys_begin()
    zox_sys_in(Position3D)
    zox_sys_in(ParticleEmitRate)
    zox_sys_in(Bounds3D)
    zox_sys_in(Color)
    for (int i = 0; i < it->count; i++) {
        zox_sys_i(Position3D, position3D)
        zox_sys_i(ParticleEmitRate, particleEmitRate)
        zox_sys_i(Bounds3D, bounds)
        zox_sys_i(Color, colorr)
#ifdef zox_bulk_spawning
        emit_particle3Ds(world, position3D->value, particleEmitRate->value);
#else
        emit_particle3Ds_slow(world, position3D->value, bounds->value, particleEmitRate->value, colorr->value);
#endif
    }
} zoxd_system(Particle3DEmitSystem)
