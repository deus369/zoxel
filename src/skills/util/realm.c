void spawn_realm_skills(ecs_world_t *world, const ecs_entity_t realm) {
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

    SkillLinks *skills = &((SkillLinks) { 0, NULL });
    initialize_memory_component(SkillLinks, skills, ecs_entity_t, realm_skills_count)
    // aura - damage one
    // char *name = generate_name();
    // todo: perhaps life aura can effect character themself!

    meta_skill_punch = spawn_realm_skill_melee(world,
        "punch",
        -1,
        -3,
        3,
        1,
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

    skills->value[0] = meta_skill_punch;
    skills->value[1] = meta_skill_aura_death;
    skills->value[2] = meta_skill_aura_life;
    skills->value[3] = meta_skill_aura_fire;

    zox_set(realm, SkillLinks, { skills->length, skills->value })
#ifdef zox_log_realm_generate
    zox_log(" + generated realm [skills]\n")
#endif
}