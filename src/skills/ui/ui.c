#ifndef zox_mod_ui_skills
#define zox_mod_ui_skills

zox_declare_tag(MenuSkills)
zox_declare_tag(IconSkill)
#include "util/tooltips.c"
#include "prefabs/prefabs.c"

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
