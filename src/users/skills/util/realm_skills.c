ecs_entity_t meta_skill_aura;

void spawn_realm_skills(ecs_world_t *world, const ecs_entity_t realm) {
    SkillLinks *skills = zox_get_mut(realm, SkillLinks)
    zox_modified(realm, SkillLinks)
    initialize_memory_component(SkillLinks, skills, ecs_entity_t, 1)
    // aura - damage one
    char *name = generate_name();
    // zox_log(" + generated [skill] name [%s]\n", name)
    meta_skill_aura = spawn_meta_skill(world, name); // "aura");
    free(name);
    zox_add_tag(meta_skill_aura, Aura);
    // zox_set(meta_skill_aura, TextureLink, { files_textures[4] });
    zox_set(meta_skill_aura, TextureLink, { string_hashmap_get(files_hashmap_textures, new_string_data("magic_damage")) })
    skills->value[0] = meta_skill_aura;
}
