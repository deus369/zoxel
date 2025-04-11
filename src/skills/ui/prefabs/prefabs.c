ecs_entity_t prefab_menu_skills;
ecs_entity_t prefab_icon_skill;
ecs_entity_t prefab_frame_skill;
zox_user_menu_functions_frame_color(Skills, Skill, skills, skill, default_fill_color_frame_skill)
#include "icon_skill.c"
#include "frame_skill.c"

void spawn_prefabs_ui_skills(ecs_world_t *world) {
    prefab_icon_skill = spawn_prefab_icon_skill(world, prefab_icon_user);
    prefab_frame_skill = spawn_prefab_frame_skill(world, prefab_frame_user);
    prefab_menu_skills = spawn_prefab_menu_skills(world, prefab_window_users);
    zox_set(prefab_menu_skills, FramePrefabLink, { prefab_frame_skill })
}