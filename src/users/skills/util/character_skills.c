const int skills_count = 8; // having blank items seems to b reak it

void spawn_character_skills(ecs_world_t *world, const ecs_entity_t e, const ecs_entity_t player) {
    if (!player) return;
    zox_get_muter(e, SkillLinks, skills)
    if (!skills) return;
    initialize_memory_component(SkillLinks, skills, ecs_entity_t, skills_count)
    if (!skills->value) {
        zox_log(" ! failed allocating memory for skills\n")
        return;
    }
    for (int i = 0; i < skills->length; i++) skills->value[i] = 0; // blanks are item slots
    // first block
    if (meta_skill_aura) {
        const ecs_entity_t aura = spawn_user_skill(world, meta_skill_aura, e);
        skills->value[0] = aura;
    } else {
        zox_log(" ! meta_skill_aura not found\n")
    }
}
