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
    if (meta_skill_punch) actions->value[0] = spawn_user_skill(world, meta_skill_punch, e);
    // block item!
    /*if (meta_item_block_dirt) actions->value[1] = spawn_user_item(world, meta_item_block_dirt, e);
    if (meta_item_block_dark) actions->value[2] = spawn_user_item(world, meta_item_block_dark, e);
    if (meta_item_block_sand) actions->value[3] = spawn_user_item(world, meta_item_block_sand, e);
    if (meta_item_block_stone) actions->value[4] = spawn_user_item(world, meta_item_block_stone, e);
    if (meta_item_block_obsidian) actions->value[5] = spawn_user_item(world, meta_item_block_obsidian, e);*/
}
