ecs_entity_t meta_quest_slay_slems;

void spawn_realm_quests(ecs_world_t *world, const ecs_entity_t realm) {
    QuestLinks *quests = zox_get_mut(realm, QuestLinks)
    resize_memory_component(QuestLinks, quests, ecs_entity_t, 1)
    zox_modified(realm, QuestLinks)
    // slay them dirty slems
    meta_quest_slay_slems = spawn_meta_quest(world, "slay slems");
    // set quest objectives
    zox_set(meta_quest_slay_slems, TextureLink, { files_textures[12] });
    quests->value[0] = meta_quest_slay_slems;
}
