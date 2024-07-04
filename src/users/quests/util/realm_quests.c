ecs_entity_t meta_quest_slay_slems;

void spawn_realm_quests(ecs_world_t *world, const ecs_entity_t realm) {
    zox_get_muter(realm, QuestLinks, quests)
    // clear previous
    for (int i = 0; i < quests->length; i++) if (quests->value[i]) zox_delete(quests->value[i])
    resize_memory_component(QuestLinks, quests, ecs_entity_t, 1)
    // slay them dirty slems
    meta_quest_slay_slems = spawn_meta_quest(world, "slay slems", prefab_quest);
    // set quest objectives
    // zox_set(meta_quest_slay_slems, TextureLink, { files_textures[12] });
    zox_set(meta_quest_slay_slems, TextureLink, { string_hashmap_get(files_hashmap_textures, new_string_data("Discord")) })
    quests->value[0] = meta_quest_slay_slems;
}
