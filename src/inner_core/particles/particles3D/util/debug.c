int get_count_particle3Ds(ecs_world_t *world) {
    return zox_count_entities(world, ecs_id(Particle3D));
}

int get_count_particle3D_emitters(ecs_world_t *world) {
    return zox_count_entities(world, ecs_id(Particle3DEmitter));
}
