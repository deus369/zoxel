#include "bone.c"
ecs_entity_t prefab_bone;

void spawn_prefabs_bones(ecs_world_t* world) {
    prefab_bone = spawn_prefab_bone(world);
}
