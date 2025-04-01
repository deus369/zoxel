const int skills_count = 8; // having blank items seems to b reak it

// todo: take in npc spawn meta data, like location, biome, etc
void spawn_character_skills(ecs_world_t *world, const ecs_entity_t e, const ecs_entity_t player) {
    if (!player) return;
    SkillLinks *skills = &((SkillLinks) { 0, NULL });
    //zox_get_muter(e, SkillLinks, skills)
    //if (!skills) return;
    initialize_memory_component(SkillLinks, skills, ecs_entity_t, skills_count)
    if (!skills->value) {
        zox_log(" ! failed allocating memory for skills\n")
        return;
    }
    for (int i = 0; i < skills->length; i++) skills->value[i] = 0; // blanks are item slots

    if (meta_skill_aura_life) skills->value[0] = spawn_user_skill(world, meta_skill_aura_life, e);
    if (meta_skill_aura_death) skills->value[1] = spawn_user_skill(world, meta_skill_aura_death, e);

    zox_set(e, SkillLinks, { skills->length, skills->value })
}
