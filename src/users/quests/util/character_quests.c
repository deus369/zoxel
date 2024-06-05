const int quests_count = 1; // having blank items seems to b reak it

void spawn_character_quests(ecs_world_t *world, const ecs_entity_t e, const ecs_entity_t player) {
    if (!player) return;
    QuestLinks *quests = zox_get_mut(e, QuestLinks)
    if (!quests) return;
    zox_modified(e, QuestLinks)
    initialize_memory_component(QuestLinks, quests, ecs_entity_t, quests_count)
    if (!quests->value) {
        zox_log(" ! failed allocating memory for quests\n")
        return;
    }
    for (int i = 0; i < quests->length; i++) quests->value[i] = 0; // blanks are item slots
    // first block
    if (meta_quest_slay_slems) {
        const ecs_entity_t quest_slay_slems = spawn_user_skill(world, meta_quest_slay_slems, e);
        quests->value[0] = quest_slay_slems;
    } else {
        zox_log(" ! meta_quest_slay_slems not found\n")
    }
}
