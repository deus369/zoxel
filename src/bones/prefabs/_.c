#include "bone.c"
entity prefab_bone;

void spawn_prefabs_bones(ecs* world) {
    prefab_bone = spawn_prefab_bone(world);
}
