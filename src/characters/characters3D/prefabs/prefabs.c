#include "character3D.c"
ecs_entity_t prefab_character3D;
ecs_entity_t prefab_character3D_player;
ecs_entity_t prefab_character3D_npc;
ecs_entity_t local_character3D;

void spawn_prefabs_characters3D(ecs_world_t *world) {
    prefab_character3D = spawn_prefab_character3D(world, prefab_vox);
}