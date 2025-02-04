#include "character3D.c"
ecs_entity_t prefab_character3D = 0;
ecs_entity_t local_character3D = 0;

void spawn_prefabs_characters3D(ecs_world_t *world) {
    prefab_character3D = spawn_prefab_character3D(world, prefab_vox);
}
