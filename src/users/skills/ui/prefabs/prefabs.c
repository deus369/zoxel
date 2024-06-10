ecs_entity_t prefab_menu_skills;
ecs_entity_t prefab_icon_skill;
// #include "menu_skills.c"
zox_user_menu_functions(Skills, Skill, skills, skill)
#include "icon_skill.c"

void spawn_prefabs_ui_skills(ecs_world_t *world) {
    prefab_icon_skill = spawn_prefab_icon_skill(world, prefab_icon_user);
    prefab_menu_skills = spawn_prefab_menu_skills(world, prefab_window_users);
}
