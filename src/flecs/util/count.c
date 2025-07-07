#define zox_count_ids(id)\
    (int) ecs_count_id(world, id);

#define zox_count_entity(type)\
    zox_count_entity_id(ecs_id(type))

int zox_count_entities(ecs_world_t *world, const ecs_entity_t id) {
    return zox_count_ids(id)
}