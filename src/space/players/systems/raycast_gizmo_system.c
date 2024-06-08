void RaycastGizmoSystem(ecs_iter_t *it) {
#ifdef zox_disable_raycast_gizmos
    return;
#endif
    zox_iter_world()
    zox_field_in(CameraLink, cameraLinks, 1)
    zox_field_in(VoxLink, voxLinks, 2)
    zox_field_out(RaycastVoxelData, raycastVoxelDatas, 3)
    for (int i = 0; i < it->count; i++) {
        zox_field_i(CameraLink, cameraLinks, cameraLink)
        zox_field_i(VoxLink, voxLinks, voxLink)
        zox_field_o(RaycastVoxelData, raycastVoxelDatas, raycastVoxelData)
        raycast_terrain_gizmo(world, cameraLink->value, voxLink->value, raycastVoxelData);
    }
} zox_declare_system(RaycastGizmoSystem)
