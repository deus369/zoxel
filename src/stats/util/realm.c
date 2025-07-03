// spawn prefabs for each meta stats
void spawn_realm_stats(ecs_world_t *world, ecs_entity_t realm) {
    if (!zox_has(realm, StatLinks)) {
        zox_log("! realm does not have StatLinks [%lu]\n", realm)
        return;
    }
    // zox_get_muter(realm, StatLinks, stats)
    zox_geter(realm, StatLinks, oldStats)
    if (oldStats) {
        // clear previous
        for (int i = 0; i < oldStats->length; i++) {
            const ecs_entity_t stat = oldStats->value[i];
            if (zox_valid(stat)) {
                zox_delete(stat)
            }
        }
    }
    StatLinks *stats = &((StatLinks) { 0, NULL });
    resize_memory_component(StatLinks, stats, ecs_entity_t, 16)

    stats->value[1] = create_stat_level(world, "soul");
    zox_add_tag(stats->value[1], StatSoul)
    zox_set(stats->value[1], TextureLink, { string_hashmap_get(files_hashmap_textures, new_string_data("soul")) })
    realm_stat_soul = stats->value[1];

    // States
    stats->value[0] = create_stat_state(world, "health");
    zox_add_tag(stats->value[0], HealthStat)
    zox_set(stats->value[0], TextureLink, { string_hashmap_get(files_hashmap_textures, new_string_data("health")) })
    realm_stat_health = stats->value[0];

    stats->value[2] = create_stat_state(world, "energy");
    zox_set(stats->value[2], TextureLink, { string_hashmap_get(files_hashmap_textures, new_string_data("energy")) })
    realm_stat_energy = stats->value[2];

    stats->value[3] = create_stat_state(world, "mana");
    zox_set(stats->value[3], TextureLink, { string_hashmap_get(files_hashmap_textures, new_string_data("mana")) })
    realm_stat_mana = stats->value[3];

    // Regens

    stats->value[4] = create_stat_regen(world, "health regen");
    zox_set(stats->value[4], TextureLink, { string_hashmap_get(files_hashmap_textures, new_string_data("healthregen")) })
    realm_stat_regen_health = stats->value[4];

    stats->value[5] = create_stat_regen(world, "energy regen");
    zox_set(stats->value[5], TextureLink, { string_hashmap_get(files_hashmap_textures, new_string_data("energyregen")) })
    realm_stat_regen_energy = stats->value[5];

    stats->value[6] = create_stat_regen(world, "mana regen");
    zox_set(stats->value[6], TextureLink, { string_hashmap_get(files_hashmap_textures, new_string_data("manaregen")) })
    realm_stat_regen_mana = stats->value[6];

    // Attributes
    stats->value[7] = create_stat_attribute(world, "strength");
    zox_set(stats->value[7], TextureLink, { string_hashmap_get(files_hashmap_textures, new_string_data("strength")) })

    stats->value[8] = create_stat_attribute(world, "vitality");
    zox_set(stats->value[8], TextureLink, { string_hashmap_get(files_hashmap_textures, new_string_data("vitality")) })

    stats->value[9] = create_stat_attribute(world, "endurance");
    zox_set(stats->value[9], TextureLink, { string_hashmap_get(files_hashmap_textures, new_string_data("endurance")) })

    stats->value[10] = create_stat_attribute(world, "intelligence");
    zox_set(stats->value[10], TextureLink, { string_hashmap_get(files_hashmap_textures, new_string_data("intelligence")) })
    stats->value[11] = create_stat_attribute(world, "wisdom");
    zox_set(stats->value[11], TextureLink, { string_hashmap_get(files_hashmap_textures, new_string_data("wisdom")) })
    stats->value[12] = create_stat_attribute(world, "agility");
    zox_set(stats->value[12], TextureLink, { string_hashmap_get(files_hashmap_textures, new_string_data("agility")) })
    stats->value[13] = create_stat_attribute(world, "dexterity");
    zox_set(stats->value[13], TextureLink, { string_hashmap_get(files_hashmap_textures, new_string_data("dexterity")) })
    stats->value[14] = create_stat_attribute(world, "charm");
    zox_set(stats->value[14], TextureLink, { string_hashmap_get(files_hashmap_textures, new_string_data("charm")) })
    stats->value[15] = create_stat_attribute(world, "luck");
    zox_set(stats->value[15], TextureLink, { string_hashmap_get(files_hashmap_textures, new_string_data("luck")) })

    // Jobs
    // create regen stat
    // statLinks->value[1] = create_stat_level(world, "farming");

    zox_set(realm, StatLinks, { stats->length, stats->value })
#ifdef zox_log_realm_generate
    zox_log(" + generated realm [stats]\n")
#endif
}