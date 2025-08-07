#include "zext.c"
entity prefab_zext;

void spawn_prefabs_texts(ecs *world) {
    prefab_zext = spawn_prefab_zext(world, prefab_layout2);
}