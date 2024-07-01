ecs_entity_t prefab_aura;
ecs_entity_t prefab_poison;
zox_create_user_data_prefabs(Skill, skill, "skill")
#include "aura.c"
#include "poison.c"

void spawn_prefabs_skills(ecs_world_t *world) {
    zox_prefab_add(prefab_realm, SkillLinks)
    zox_prefab_add(prefab_character3D, SkillLinks)
    prefab_skill = spawn_prefab_skill(world);
    prefab_aura = spawn_prefab_aura(world, prefab_skill);
    prefab_poison = spawn_prefab_poison(world);
}
