void spawn_prefabs_quests(ecs_world_t *world) {
    zox_prefab_add(prefab_realm, QuestLinks)
    zox_prefab_add(prefab_character3D, QuestLinks)
    prefab_quest = spawn_prefab_quest(world);
}
