int get_count_particle3Ds(ecs_world_t *world) {
    return zox_count_types(Particle3D)
}

int get_count_particle3D_emitters(ecs_world_t *world) {
    return zox_count_types(Particle3DEmitter)
}
