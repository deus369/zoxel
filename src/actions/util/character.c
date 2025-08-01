const int actions_count = 8; // 10; // having blank items seems to b reak it

void spawn_character_actions(ecs_world_t *world, spawned_character3D_data *data) {
    if (!data->p) {
        return;
    }
    ActionLinks *actions = &((ActionLinks) { 0, NULL });
    initialize_ActionLinks(actions, actions_count);
    if (!actions->value) {
        zox_log(" ! failed allocating memory for actions\n")
        return;
    }
    for (int i = 0; i < actions->length; i++) {
        actions->value[i] = 0; // blanks are item slots
    }
    // skill!
    int place_index = 0;
    if (meta_skill_punch) {
        actions->value[place_index++] = spawn_user_skill(world, meta_skill_punch, data->e);
    }
    if (test_actions_skills) {
        if (meta_skill_aura_death) {
            actions->value[place_index++] = spawn_user_skill(world, meta_skill_aura_death, data->e);
        }
        if (meta_skill_aura_life) {
            actions->value[place_index++] = spawn_user_skill(world, meta_skill_aura_life, data->e);
        }
        if (meta_skill_aura_fire) {
            actions->value[place_index++] = spawn_user_skill(world, meta_skill_aura_fire, data->e);
        }
    }
    if (test_actions_blocks) {
        if (meta_item_block_dungeon_core) {
            actions->value[place_index++] = spawn_user_item(world, meta_item_block_dungeon_core, data->e);
        }
        if (meta_item_block_dark) {
            actions->value[place_index++] = spawn_user_item(world, meta_item_block_dark, data->e);
            zox_set(actions->value[place_index - 1], Quantity, { 12 })
        }
    }
    zox_set(data->e, ActionLinks, { actions->length, actions->value })
}

// block item!
/*if (meta_item_block_dirt) actions->value[1] = spawn_user_item(world, meta_item_block_dirt, e);
 i f (meta_item_block_dark) actions->value[2] = spawn_user_item(world, meta_item_block_dark, e);          *
 if (meta_item_block_sand) actions->value[3] = spawn_user_item(world, meta_item_block_sand, e);
 if (meta_item_block_stone) actions->value[4] = spawn_user_item(world, meta_item_block_stone, e);
 if (meta_item_block_obsidian) actions->value[5] = spawn_user_item(world, meta_item_block_obsidian, e);*/
