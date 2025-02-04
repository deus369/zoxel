// spawn prefabs for each meta stats
void spawn_realm_stats(ecs_world_t *world, ecs_entity_t realm) {
    zox_get_muter(realm, StatLinks, stats)
    // clear previous
    for (int i = 0; i < stats->length; i++) if (stats->value[i]) zox_delete(stats->value[i])
    resize_memory_component(StatLinks, stats, ecs_entity_t, 16)

    meta_stat_soul = create_stat_level(world, "soul");
    zox_set(meta_stat_soul, TextureLink, { string_hashmap_get(files_hashmap_textures, new_string_data("soul")) })
    stats->value[1] = meta_stat_soul;
    zox_add_tag(meta_stat_soul, StatSoul)

    // States
    meta_stat_health = create_stat_state(world, "health");
    zox_set(meta_stat_health, TextureLink, { string_hashmap_get(files_hashmap_textures, new_string_data("health")) })
    zox_add_tag(meta_stat_health, HealthStat)
    stats->value[0] = meta_stat_health;

    stats->value[2] = create_stat_state(world, "energy");
    meta_stat_energy = stats->value[2];
    zox_set(meta_stat_energy, TextureLink, { string_hashmap_get(files_hashmap_textures, new_string_data("energy")) })

    stats->value[3] = create_stat_state(world, "mana");
    meta_stat_mana = stats->value[3];
    zox_set(meta_stat_mana, TextureLink, { string_hashmap_get(files_hashmap_textures, new_string_data("mana")) })

    // Regens

    stats->value[4] = create_stat_regen(world, "health regen");
    meta_stat_regen_health = stats->value[4];
    zox_set(meta_stat_regen_health, TextureLink, { string_hashmap_get(files_hashmap_textures, new_string_data("healthregen")) })

    stats->value[5] = create_stat_regen(world, "energy regen");
    zox_set(stats->value[5], TextureLink, { string_hashmap_get(files_hashmap_textures, new_string_data("energyregen")) })
    meta_stat_regen_energy = stats->value[5];

    stats->value[6] = create_stat_regen(world, "mana regen");
    zox_set(stats->value[6], TextureLink, { string_hashmap_get(files_hashmap_textures, new_string_data("manaregen")) })
    meta_stat_regen_mana = stats->value[6];

    // Attributes

    stats->value[7] = create_stat_attribute(world, "strength");
    zox_set(stats->value[7], TextureLink, { string_hashmap_get(files_hashmap_textures, new_string_data("strength")) })
    meta_stat_strength = stats->value[7];


    stats->value[8] = create_stat_attribute(world, "vitality");
    stats->value[9] = create_stat_attribute(world, "endurance");
    stats->value[10] = create_stat_attribute(world, "intelligence");
    stats->value[11] = create_stat_attribute(world, "wisdom");
    stats->value[12] = create_stat_attribute(world, "agility");
    stats->value[13] = create_stat_attribute(world, "dexterity");
    stats->value[14] = create_stat_attribute(world, "charm");
    stats->value[15] = create_stat_attribute(world, "luck");

    // Jobs
    // create regen stat
    // statLinks->value[1] = create_stat_level(world, "farming");
#ifdef zox_log_realm_generate
    zox_log(" + generated realm [stats]\n")
#endif
}
