#include "character3_meta.c"
#include "character3.c"
#include "character3_instanced.c"
ecs_entity_t prefab_character3_meta;
ecs_entity_t prefab_character3;
ecs_entity_t prefab_character3_player;
ecs_entity_t prefab_character3_npc;
ecs_entity_t local_character3D;
ecs_entity_t prefab_character3_instanced;

void spawn_prefabs_characters3D(ecs_world_t *world) {
    prefab_character3_meta = spawn_prefab_character3_meta(world);
    prefab_character3 = spawn_prefab_character3(world, prefab_vox);
    // prefab_character3_instanced = spawn_prefab_character3_instanced(world, prefab_vox_instanced);
    if (prefab_realm) {
        zox_prefab_add(prefab_realm, CharacterLinks)
        zox_prefab_set(prefab_realm, CharactersChanceMax, { 0 })
    }
}