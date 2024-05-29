// todo: fix edge of chunk not updating
// todo: fix block voxes not destroying
// todo: add destruction animation
// todo: hold to destroy
// todo: link to inventory
// todo: pickup items

void RaycastGizmoSystem(ecs_iter_t *it) {
    zox_iter_world()
    zox_field_in(CameraLink, cameraLinks, 1)
    zox_field_in(VoxLink, voxLinks, 2)
    for (int i = 0; i < it->count; i++) {
        zox_field_i(CameraLink, cameraLinks, cameraLink)
        zox_field_i(VoxLink, voxLinks, voxLink)
        raycast_terrain_gizmo(world, cameraLink->value, voxLink->value);
    }
} zox_declare_system(RaycastGizmoSystem)

void VoxelActionASystem(ecs_iter_t *it) {
    zox_iter_world()
    zox_field_in(CameraLink, cameraLinks, 1)
    zox_field_in(VoxLink, voxLinks, 2)
    zox_field_out(TriggerActionA, triggerActionAs, 3)
    for (int i = 0; i < it->count; i++) {
        zox_field_o(TriggerActionA, triggerActionAs, triggerActionA)
        if (!triggerActionA->value) continue;
        triggerActionA->value = 0;
        zox_field_i(CameraLink, cameraLinks, cameraLink)
        zox_field_i(VoxLink, voxLinks, voxLink)
        raycast_terrain(world, cameraLink->value, voxLink->value, 0, 0, 2);
    }
} zox_declare_system(VoxelActionASystem)

void VoxelActionBSystem(ecs_iter_t *it) {
    zox_iter_world()
    zox_field_in(CameraLink, cameraLinks, 1)
    zox_field_in(VoxLink, voxLinks, 2)
    zox_field_out(TriggerActionB, triggerActionBs, 3)
    for (int i = 0; i < it->count; i++) {
        zox_field_o(TriggerActionB, triggerActionBs, triggerActionB)
        if (!triggerActionB->value) continue;
        triggerActionB->value = 0;
        zox_field_i(CameraLink, cameraLinks, cameraLink)
        zox_field_i(VoxLink, voxLinks, voxLink)
        raycast_terrain(world, cameraLink->value, voxLink->value, 0, 1, 1);
    }
} zox_declare_system(VoxelActionBSystem)
