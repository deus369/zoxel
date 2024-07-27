#ifndef zox_mod_users
#define zox_mod_users

zox_component_entity(UserLink)
zox_component_entity(UserDataLink)
zox_component_entity(SpawnerLink)
zox_component_byte(Quantity)
zox_entities_component(UserLinks)
#include "util/user_data.c"
#include "ui/ui.c"
#include "combat/combat.c"
#include "stats/stats.c"
#include "skills/skills.c"
#include "items/items.c"
#include "actions/actions.c"
#include "dialogues/dialogues.c"
#include "quests/quests.c"
#include "classes/classes.c"
#include "jobs/jobs.c"
#include "races/races.c"
#include "clans/clans.c"
#include "lores/lores.c"
#include "achievements/achievements.c"

void set_taskbar_icon_active(ecs_world_t *world, const ecs_entity_t canvas, const ecs_entity_t frame, const int i) {
    if (i == taskbar_items) { if_has_child_with_tag(canvas, MenuItems) zox_set(frame, ActiveState, { 1 }) }
    else if (i == taskbar_skills) {if_has_child_with_tag(canvas, MenuSkills) zox_set(frame, ActiveState, { 1 }) }
    else if (i == taskbar_quests) {if_has_child_with_tag(canvas, MenuQuests) zox_set(frame, ActiveState, { 1 }) }
    else if (i == taskbar_stats) {if_has_child_with_tag(canvas, MenuStats) zox_set(frame, ActiveState, { 1 }) }
    else if (i == taskbar_actions) {if_has_child_with_tag(canvas, MenuActions) zox_set(frame, ActiveState, { 1 }) }
}

void on_toggle_taskbar_icon(ecs_world_t *world, const ClickEventData *event) {
    const ecs_entity_t canvas = zox_get_value(event->clicker, CanvasLink)
    const unsigned char index = zox_get_value(event->clicked, IconIndex)
    if (index == taskbar_menu) toggle_ui_with_tag_e(spawn_menu_paused_player, MenuPaused, event->clicker)
    else if (index == taskbar_stats) toggle_ui_with_tag_e(spawn_menu_stats_player, MenuStats, event->clicker)
    else if (index == taskbar_items) toggle_ui_with_tag_e(spawn_menu_items_player, MenuItems, event->clicker)
    else if (index == taskbar_skills) toggle_ui_with_tag_e(spawn_menu_skills_player, MenuSkills, event->clicker)
    else if (index == taskbar_quests) toggle_ui_with_tag_e(spawn_menu_quests_player, MenuQuests, event->clicker)
    // testing - spawn_actionbar_player
    else if (index == taskbar_actions) toggle_ui_with_tag_e(spawn_menu_actions_player, MenuActions, event->clicker)
    else return; // nothing to open
    // toggle frames active state
    const ecs_entity_t frame = zox_get_value(event->clicked, ParentLink)
    if (!frame || !zox_has(frame, ActiveState)) {
        zox_log(" ! invalid frame\n")
        return;
    }
    zox_set(frame, ActiveState, { !zox_gett_value(frame, ActiveState) })
}

zox_begin_module(Users)
zox_define_component_entity(UserLink)
zox_define_component_entity(UserDataLink)
zox_define_component_entity(SpawnerLink)
zox_define_component_byte(Quantity)
zox_define_entities_component(UserLinks)
zox_import_module(UsersUI)
zox_import_module(Combat)
zox_import_module(Stats)
zox_import_module(Skills)
zox_import_module(Items)
zox_import_module(Actions)
zox_import_module(Dialogues)
zox_import_module(Quests)
zox_import_module(Classes)
zox_import_module(Jobs)
zox_import_module(Races)
zox_import_module(Clans)
zox_import_module(Lores)
zox_import_module(Achievements)
zoxel_end_module(Users)

#endif
