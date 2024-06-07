void Particle3DEmitSystem(ecs_iter_t *it) {
    zox_iter_world()
    zox_field_in(Position3D, position3Ds, 1)
    zox_field_in(ParticleEmitRate, particleEmitRates, 2)
    zox_field_in(Bounds3D, boundss, 3)
    for (int i = 0; i < it->count; i++) {
        zox_field_i(Position3D, position3Ds, position3D)
        zox_field_i(ParticleEmitRate, particleEmitRates, particleEmitRate)
        zox_field_i(Bounds3D, boundss, bounds)
#ifdef zox_bulk_spawning
        emit_particle3Ds(world, position3D->value, particleEmitRate->value);
#else
        emit_particle3Ds_slow(world, position3D->value, bounds->value, particleEmitRate->value);
#endif
    }
} zox_declare_system(Particle3DEmitSystem)
