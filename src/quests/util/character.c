const int quests_count = 1; // having blank items seems to b reak it

void spawn_character_quests(ecs_world_t *world, spawned_character3D_data *data) {
    if (!data->p) {
        return;
    }
    QuestLinks *quests = &((QuestLinks) { 0, NULL });
    initialize_memory_component(QuestLinks, quests, ecs_entity_t, quests_count)
    if (!quests->value) {
        zox_log_error(" ! failed allocating memory for quests")
        return;
    }
    for (int i = 0; i < quests->length; i++) {
        quests->value[i] = 0; // blanks are item slots
    }
    // first block
    if (meta_quest_slay_slems) {
        const ecs_entity_t quest_slay_slems = spawn_user_quest(world, meta_quest_slay_slems, data->e);
        quests->value[0] = quest_slay_slems;
    } else {
        zox_log_error(" ! meta_quest_slay_slems not found")
    }
    zox_set(data->e, QuestLinks, { quests->length, quests->value })
}