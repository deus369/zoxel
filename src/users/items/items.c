#ifndef zoxel_items
#define zoxel_items

zox_declare_user_data(Item)
#include "prefabs/item.c"

void spawn_prefabs_items(ecs_world_t *world) {
    spawn_prefab_item(world);
}

zox_begin_module(Items)
zox_define_user_data(Item)
zoxel_end_module(Items)

#endif
