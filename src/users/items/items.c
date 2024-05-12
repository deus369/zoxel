#ifndef zox_items
#define zox_items

zox_declare_user_data(Item)
#include "prefabs/item.c"
#include "ui/ui.c"

void spawn_prefabs_items(ecs_world_t *world) {
    spawn_prefab_item(world);
    spawn_prefabs_items_ui(world);
}

zox_begin_module(Items)
zox_define_user_data(Item)
zox_import_module(ItemsUI)
zoxel_end_module(Items)

#endif
