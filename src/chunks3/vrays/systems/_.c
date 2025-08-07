#include "chunk3_raycast.c"
#include "raycast_gizmo.c"

void define_systems_vrays(ecs_world_t* world) {
    zox_system(Chunk3RaycastSystem, EcsOnUpdate,
            [in] cameras.CameraLink,
            [in] chunks3.VoxLink,
            [in] vrays.RaycastRange,
            [out] vrays.RaycastVoxelData);
    zox_system_1(RaycastGizmoSystem, EcsPreStore,
            [in] vrays.RaycastVoxelData);
}