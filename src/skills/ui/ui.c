#ifndef zox_mod_ui_skills
#define zox_mod_ui_skills

zox_declare_tag(MenuSkills)
zox_declare_tag(IconSkill)
zox_declare_tag(FrameSkill)
#include "prefabs/prefabs.c"
#include "util/icon.c"
#include "systems/skill_overlay_system.c"

zox_begin_module(UISkills)
    zox_define_tag(MenuSkills)
    zox_define_tag(IconSkill)
    zox_define_tag(FrameSkill)
    // note: action uis doesn't have same things'
    zox_system(SkillOverlaySystem, EcsOnUpdate, [in] users.UserDataLink, [in] hierarchys.Children, [none] elements2.Icon)
    spawn_prefabs_ui_skills(world);
    add_taskbar_button((hook_taskbar) {
        .spawn = &spawn_player_menu_skills,
        .component_id = MenuSkills,
        .texture_name = "taskbar_skills"
    });
zox_end_module(UISkills)

#endif