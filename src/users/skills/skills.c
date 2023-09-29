#ifndef zoxel_skills
#define zoxel_skills

zox_declare_user_data(Skill)
zox_declare_tag(Aura)
#include "prefabs/skill.c"
#include "systems/aoe_damage_system.c"

void spawn_prefabs_skills(ecs_world_t *world) {
    spawn_prefab_skill(world);
}

zox_begin_module(Skills)
zox_define_user_data(Skill)
zox_define_tag(Aura)
zox_filter(characters, [in] Position3D, [in] UserStatLinks)
zox_system_ctx(AOEDamageSystem, EcsOnUpdate, characters, [none] Aura, [in] Position3D)
zoxel_end_module(Skills)

#endif