ecs_entity_t prefab_actionbar;
ecs_entity_t prefab_icon_frame_action;
#include "icon_frame_action.c"
#include "actionbar.c"

void spawn_prefabs_actions_ui(ecs_world_t *world) {
    prefab_icon_frame_action = spawn_prefab_icon_frame_action(world, prefab_element);
    prefab_actionbar = spawn_prefab_actionbar(world, prefab_element);
}
