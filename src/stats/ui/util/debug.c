int get_statbars_count(ecs_world_t *world) {
    return zox_count_entities(world, ecs_id(Statbar));
}