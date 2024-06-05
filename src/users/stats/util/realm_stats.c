// spawn prefabs for each meta stats
void spawn_realm_stats(ecs_world_t *world, ecs_entity_t realm) {
    StatLinks *stats = zox_get_mut(realm, StatLinks)
    resize_memory_component(StatLinks, stats, ecs_entity_t, 16)

    meta_stat_health = create_stat_state(world, "health");
    zox_set(meta_stat_health, TextureLink, { files_textures[26] });
    zox_add_tag(meta_stat_health, HealthStat)
    stats->value[0] = meta_stat_health;

    meta_stat_soul = create_stat_level(world, "soul");
    zox_set(meta_stat_soul, TextureLink, { files_textures[11] });
    zox_add_tag(meta_stat_soul, HealthStat)
    stats->value[1] = meta_stat_soul;

    stats->value[2] = create_stat_state(world, "energy");
    stats->value[3] = create_stat_state(world, "mana");
    meta_stat_energy = stats->value[2];
    zox_set(meta_stat_energy, TextureLink, { files_textures[25] });
    meta_stat_mana = stats->value[3];
    zox_set(meta_stat_mana, TextureLink, { files_textures[24] });

    stats->value[4] = create_stat_regen(world, "health regen");
    meta_stat_regen_health = stats->value[4];
    zox_set(meta_stat_regen_health, TextureLink, { files_textures[1] }); // health_regen.png
    stats->value[5] = create_stat_regen(world, "mana regen");
    stats->value[6] = create_stat_regen(world, "energy regen");


    stats->value[7] = create_stat_attribute(world, "strength");
    stats->value[8] = create_stat_attribute(world, "vitality");
    stats->value[9] = create_stat_attribute(world, "endurance");
    stats->value[10] = create_stat_attribute(world, "intelligence");
    stats->value[11] = create_stat_attribute(world, "wisdom");
    stats->value[12] = create_stat_attribute(world, "agility");
    stats->value[13] = create_stat_attribute(world, "dexterity");
    stats->value[14] = create_stat_attribute(world, "charm");
    stats->value[15] = create_stat_attribute(world, "luck");
    // create regen stat
    // statLinks->value[1] = create_stat_level(world, "farming");
    zox_modified(realm, StatLinks)
}
