ecs_entity_t meta_skill_aura_life;
ecs_entity_t meta_skill_aura_death;
ecs_entity_t meta_skill_punch;

void spawn_realm_skills(ecs_world_t *world, const ecs_entity_t realm) {
    if (!zox_has(realm, SkillLinks)) {
        zox_log("! realm does not have SkillLinks [%lu]\n", realm)
        return;
    }
    /*zox_get_muter(realm, SkillLinks, skills)
    if (!skills) {
        zox_log("! realm skills was null [%lu]\n", realm)
        return;
    }*/
    // clear previous
    zox_geter(realm, SkillLinks, oldSkills)
    if (oldSkills) {
        for (int i = 0; i < oldSkills->length; i++) {
            if (oldSkills->value[i]) zox_delete(oldSkills->value[i])
        }
    }

    SkillLinks *skills = &((SkillLinks) { 0, NULL });
    initialize_memory_component(SkillLinks, skills, ecs_entity_t, 3)
    // aura - damage one
    // char *name = generate_name();
    // todo: perhaps life aura can effect character themself!

    meta_skill_punch = spawn_skill_melee(world, prefab_skill_melee, "punch", -1, 3.5f, 1);
    zox_set(meta_skill_punch, TextureLink, { string_hashmap_get(files_hashmap_textures, new_string_data("punch")) })
    skills->value[0] = meta_skill_punch;

    meta_skill_aura_death = spawn_skill_aura(world, prefab_skill_aura, "death aura", -1, 3, (color) { 5, 5, 5, 122 });
    zox_set(meta_skill_aura_death, TextureLink, { string_hashmap_get(files_hashmap_textures, new_string_data("aura_death")) })
    skills->value[1] = meta_skill_aura_death;
    meta_skill_aura_life = spawn_skill_aura(world, prefab_skill_aura, "life aura", 1, 3, (color) { 255, 255, 255, 88 });
    zox_set(meta_skill_aura_life, TextureLink, { string_hashmap_get(files_hashmap_textures, new_string_data("aura_life")) })
    skills->value[2] = meta_skill_aura_life;

    zox_set(realm, SkillLinks, { skills->length, skills->value })
#ifdef zox_log_realm_generate
    zox_log(" + generated realm [skills]\n")
#endif
}
