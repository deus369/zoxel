#include "character3D_npc.c"
ecs_entity_t prefab_character3_npc;
ecs_entity_t prefab_character3_instanced_npc;

#define zox_prefab_character_npc_set(T, ...)\
    zox_prefab_set(prefab_character3_npc, T, __VA_ARGS__)\
    zox_prefab_set(prefab_character3_instanced, T, __VA_ARG)

void spawn_prefabs_npcs(ecs_world_t *world) {
    prefab_character3_npc = spawn_prefab_character3_npc(world, prefab_character3);
    prefab_character3_instanced_npc = spawn_prefab_character3_npc(world, prefab_character3_instanced);
    prefabs_characters3[prefab_characters_count++] = prefab_character3_npc;
    prefabs_characters3[prefab_characters_count++] = prefab_character3_instanced_npc;
}