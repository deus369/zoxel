#ifndef zox_mod_ui_skills
#define zox_mod_ui_skills

// todo: when use aura skill - set overlay frame on or off
zox_declare_tag(MenuSkills)
zox_declare_tag(IconSkill)
#include "prefabs/prefabs.c"
#include "util/icon.c"

zox_begin_module(UISkills)
    zox_define_tag(MenuSkills)
    zox_define_tag(IconSkill)
    spawn_prefabs_ui_skills(world);
    add_taskbar_button((hook_taskbar) {
        .spawn = &spawn_player_menu_skills,
        .component_id = MenuSkills,
        .texture_name = "taskbar_skills"
    });
zox_end_module(UISkills)

#endif