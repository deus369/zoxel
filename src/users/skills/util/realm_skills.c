ecs_entity_t meta_skill_aura_life;
ecs_entity_t meta_skill_aura_death;
ecs_entity_t meta_skill_punch;

void spawn_realm_skills(ecs_world_t *world, const ecs_entity_t realm) {
    zox_get_muter(realm, SkillLinks, skills)
    // clear previous
    for (int i = 0; i < skills->length; i++) if (skills->value[i]) zox_delete(skills->value[i])
    initialize_memory_component(SkillLinks, skills, ecs_entity_t, 3)
    // aura - damage one
    // char *name = generate_name();

    // todo: create unique particles for each aura effect
    // todo: perhaps life aura can effect character themself!


    meta_skill_punch = spawn_meta_skill(world, prefab_aura, "punch");
    zox_set(meta_skill_punch, TextureLink, { string_hashmap_get(files_hashmap_textures, new_string_data("punch")) })
    skills->value[0] = meta_skill_punch;


    meta_skill_aura_death = spawn_meta_skill_aura(world, prefab_aura, "death aura", -1, 3, (color) { 0, 0, 0, 122 });
    zox_set(meta_skill_aura_death, TextureLink, { string_hashmap_get(files_hashmap_textures, new_string_data("aura_death")) })
    skills->value[1] = meta_skill_aura_death;
    meta_skill_aura_life = spawn_meta_skill_aura(world, prefab_aura, "life aura", 1, 3, (color) { 255, 255, 255, 88 });
    zox_set(meta_skill_aura_life, TextureLink, { string_hashmap_get(files_hashmap_textures, new_string_data("aura_life")) })
    skills->value[2] = meta_skill_aura_life;
}
