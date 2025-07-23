void spawn_realm_skills(ecs_world_t *world, const ecs_entity_t realm) {
    const float base_death_aura_damage = 1;
    const float base_death_aura_range = 3;

    if (!zox_has(realm, SkillLinks)) {
        zox_log("! realm does not have SkillLinks [%lu]\n", realm)
        return;
    }
    // clear previous
    zox_geter(realm, SkillLinks, oldSkills)
    if (oldSkills) {
        for (int i = 0; i < oldSkills->length; i++) {
            if (oldSkills->value[i]) zox_delete(oldSkills->value[i])
        }
    }

    zox_geter(realm, StatLinks, stats)
    SkillLinks *skills = &((SkillLinks) { 0, NULL });
    // aura - damage one
    // char *name = generate_name();
    // todo: perhaps life aura can effect character themself!

    ecs_entity_t health = 0;
    ecs_entity_t energy = 0;
    ecs_entity_t mana = 0;
    for (int i = 0; i < stats->length; i++) {
        const ecs_entity_t stat = stats->value[i];
        if (zox_has(stat, StatState)) {
            if (!health) {
                health = stat;
            } else if (!energy) {
                energy = stat;
            } else if (!mana) {
                mana = stat;
            }
        }
    }

    meta_skill_punch = spawn_realm_skill_melee(world,
        "punch",
        1,
        3,
        3,
        energy,
        1,
        "punch");

    // testing

    ecs_entity_t mana_punch = spawn_realm_skill_melee(world,
        "mana punch",
        5,
        8,
        3,
        mana,
        3,
        "punch");
    // zox_set(meta_skill_punch, TextureLink, { string_hashmap_get(files_hashmap_textures, new_string_data("punch")) })

    meta_skill_aura_death = spawn_realm_skill_aura(world,
        "death aura",
        -base_death_aura_damage,
        base_death_aura_range,
        (color) { 5, 5, 5, 122 },
        "aura_death");
    meta_skill_aura_life = spawn_realm_skill_aura(world,
        "life aura",
        base_death_aura_damage,
        base_death_aura_range,
        (color) { 255, 255, 255, 88 },
        "aura_life");
    meta_skill_aura_fire = spawn_realm_skill_aura(world,
        "fire aura",
        -base_death_aura_damage * 0.5f,
        base_death_aura_range * 4,
        (color) { 255, 22, 22, 144 },
        "aura_fire");

    add_to_SkillLinks(skills, meta_skill_punch);
    add_to_SkillLinks(skills, mana_punch);
    add_to_SkillLinks(skills, meta_skill_aura_death);
    add_to_SkillLinks(skills, meta_skill_aura_life);
    add_to_SkillLinks(skills, meta_skill_aura_fire);

    zox_set(realm, SkillLinks, { skills->length, skills->value })
#ifdef zox_log_realm_generate
    zox_log(" + generated realm [skills]\n")
#endif
}