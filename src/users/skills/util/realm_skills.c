ecs_entity_t meta_skill_aura;

void spawn_realm_skills(ecs_world_t *world, const ecs_entity_t realm) {
    zox_get_muter(realm, SkillLinks, skills)
    // clear previous
    for (int i = 0; i < skills->length; i++) if (skills->value[i]) zox_delete(skills->value[i])
    initialize_memory_component(SkillLinks, skills, ecs_entity_t, 1)
    // aura - damage one
    char *name = generate_name();
    // zox_log(" + generated [skill] name [%s]\n", name)
    meta_skill_aura = spawn_meta_skill(world, name, prefab_aura); // "aura");
    free(name);
    // zox_set(meta_skill_aura, TextureLink, { files_textures[4] });
    zox_set(meta_skill_aura, TextureLink, { string_hashmap_get(files_hashmap_textures, new_string_data("magic_damage")) })
    skills->value[0] = meta_skill_aura;
}
