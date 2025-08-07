#include "activate.c"

void define_systems_actions(ecs_world_t* world) {
    zox_system_1(ActionActivateSystem, EcsOnUpdate,
            [in] triggers.TriggerActionB,
            [in] actions.ActionIndex,
            [in] vrays.RaycastRange,
            [in] vrays.RaycastVoxelData,
            [out] actions.ActionLinks);
}