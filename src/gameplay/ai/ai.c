#ifndef zoxel_ai
#define zoxel_ai

zox_declare_tag(Wanderer)
#include "prefabs/character3D_npc.c"
#include "systems/wander_system.c"

void spawn_prefabs_ai(ecs_world_t *world) {
    spawn_prefab_character3D_npc(world);
}

zox_begin_module(AI)
zox_define_tag(Wanderer)
zox_system(WanderSystem, EcsOnUpdate, [none] Wanderer, [in] Rotation3D,  [in] Velocity3D, [out] Acceleration3D,  [in] Omega3D, [out] Alpha3D)
zoxel_end_module(AI)

#endif
