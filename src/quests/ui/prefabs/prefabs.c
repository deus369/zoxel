ecs_entity_t prefab_menu_quests;
ecs_entity_t prefab_icon_quest;
zox_user_menu_functions(Quests, Quest, quests, quest)
#include "icon_quest.c"

void spawn_prefabs_ui_quests(ecs_world_t *world) {
    prefab_icon_quest = spawn_prefab_icon_quest(world, prefab_icon_user);
    prefab_menu_quests = spawn_prefab_menu_quests(world, prefab_window_users);
}
