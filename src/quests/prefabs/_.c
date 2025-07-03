void spawn_prefabs_quests(ecs_world_t *world) {
    prefab_quest = spawn_prefab_quest(world);
    // link to core
    if (prefab_realm) {
        zox_prefab_add(prefab_realm, QuestLinks)
    }
    if (prefab_character3D) {
        zox_prefab_add(prefab_character3D, QuestLinks)
    }
}
