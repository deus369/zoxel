ecs_entity_t spawn_prefab_texture(ecs_world_t *world, const int2 texture_size) {
    zox_prefab()
    zox_prefab_name("prefab_texture")
    add_texture_non_generate(world, e, texture_size);
    return e;
}

ecs_entity_t spawn_texture_dirt(ecs_world_t *world, const ecs_entity_t prefab, const int seed, const color fill_color) {
    zox_instance(prefab)
    zox_name("texture")
    zox_set(e, Seed, { seed })
    zox_set(e, Color, { fill_color })
    return e;
}
