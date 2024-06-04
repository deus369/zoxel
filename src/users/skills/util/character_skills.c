const int skills_count = 1; // having blank items seems to b reak it

void spawn_character_skills(ecs_world_t *world, const ecs_entity_t e, const ecs_entity_t player) {
    if (!player) return;
    SkillLinks *skills = zox_get_mut(e, SkillLinks)
    if (!skills) return;
    initialize_memory_component(SkillLinks, skills, ecs_entity_t, skills_count)
    if (!skills->value) {
        zox_log(" ! failed allocating memory for skills\n")
        return;
    }
    for (int i = 0; i < skills->length; i++) skills->value[i] = 0; // blanks are item slots
    // first block
    if (meta_item_aura) {
        const ecs_entity_t aura = spawn_user_skill(world, meta_item_aura, e);
        skills->value[0] = aura;
    } else {
        zox_log(" ! meta_item_aura not found\n")
    }
    zox_modified(e, SkillLinks)
}
