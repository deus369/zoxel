#include "activate.c"

void define_systems_actions(ecs_world_t* world) {
    zox_system_1(ActionActivateSystem, EcsOnUpdate,
            [in] triggers.TriggerActionB,
            [in] actions.ActionIndex,
            [in] chunks3.RaycastRange,
            [in] chunks3.RaycastVoxelData,
            [out] actions.ActionLinks);
}