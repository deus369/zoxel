ecs_entity_t prefab_aura;
ecs_entity_t prefab_poison;
ecs_entity_t prefab_skill;

#include "skill.c"
#include "aura.c"
#include "poison.c"

void spawn_prefabs_skills(ecs_world_t *world) {
    prefab_skill = spawn_prefab_skill(world);
    prefab_aura = spawn_prefab_aura(world);
    prefab_poison = spawn_prefab_poison(world);
    zox_prefab_add(prefab_character3D, SkillLinks)
}
