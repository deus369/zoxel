#include "chunk3_raycast.c"
#include "raycast_gizmo.c"

void define_systems_players2(ecs_world_t *world) {
    zox_system(Chunk3RaycastSystem, EcsOnUpdate,
            [in] cameras.CameraLink,
            [in] chunks3.VoxLink,
            [in] chunks3.RaycastRange,
            [out] chunks3.RaycastVoxelData);
    zox_system_1(RaycastGizmoSystem, EcsPreStore,
            [in] chunks3.RaycastVoxelData);
}