const int actions_count = 8; // 10; // having blank items seems to b reak it

void spawn_character_actions(ecs_world_t *world, const ecs_entity_t e, const ecs_entity_t player) {
    if (!player) return;
    zox_get_muter(e, ActionLinks, actions)
    if (!actions) return;
    initialize_memory_component(ActionLinks, actions, ecs_entity_t, actions_count)
    if (!actions->value) {
        zox_log(" ! failed allocating memory for actions\n")
        return;
    }
    for (int i = 0; i < actions->length; i++) actions->value[i] = 0; // blanks are item slots
    // skill!
    if (meta_skill_aura) {
        actions->value[0] = spawn_user_skill(world, meta_skill_aura, e);
    } else {
        zox_log(" ! meta_skill_aura not found\n")
    }
    // block item!
    if (meta_item_block) {
        actions->value[1] = spawn_user_item(world, meta_item_block, e);
    } else {
        zox_log(" ! meta_item_block not found\n")
    }
}
