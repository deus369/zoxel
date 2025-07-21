// spawn prefabs for each meta stats
ecs_entity_t spawn_realm_stat_state(ecs_world_t* world,
    const char* name,
    char* texture_name,
    const color_rgb c)
{
    const ecs_entity_t texture = string_hashmap_get(files_hashmap_textures, new_string_data(texture_name));
    ecs_entity_t e = create_stat_state(world, name, texture, c);
    return e;
}

ecs_entity_t spawn_realm_stat_level(ecs_world_t* world,
    const char* name,
    char* texture_name,
    const color_rgb c)
{
    const ecs_entity_t texture = string_hashmap_get(files_hashmap_textures, new_string_data(texture_name));
    ecs_entity_t e = create_stat_level(world, name, texture, c);
    return e;
}

ecs_entity_t spawn_realm_stat_regen(ecs_world_t* world,
    const char* name,
    char* texture_name)
{
    const ecs_entity_t texture = string_hashmap_get(files_hashmap_textures, new_string_data(texture_name));
    ecs_entity_t e = create_stat_regen(world, name, texture);
    return e;
}

ecs_entity_t spawn_realm_stat_attribute(ecs_world_t* world,
    const char* name,
    char* texture_name)
{
    const ecs_entity_t texture = string_hashmap_get(files_hashmap_textures, new_string_data(texture_name));
    ecs_entity_t e = create_stat_attribute(world, name, texture);
    return e;
}
