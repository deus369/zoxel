// left click - destroy
void VoxelActionASystem(ecs_iter_t *it) {
    zox_field_world()
    zox_field_in(RaycastVoxelData, raycastVoxelDatas, 1)
    zox_field_out(TriggerActionA, triggerActionAs, 2)
    for (int i = 0; i < it->count; i++) {
        zox_field_o(TriggerActionA, triggerActionAs, triggerActionA)
        if (!triggerActionA->value) continue;
        zox_field_i(RaycastVoxelData, raycastVoxelDatas, raycastVoxelData)
        raycast_action(world, raycastVoxelData, 0, 2);
        spawn_pickup(world, prefab_pickup, raycastVoxelData->hit);
        triggerActionA->value = 0;
        // gett  position of destroying:
        // using hit for now
        // zox_log(" > spawned pickup at [%fx%fx%f]\n", raycastVoxelData->hit.x, raycastVoxelData->hit.y, raycastVoxelData->hit.z)
    }
} zox_declare_system(VoxelActionASystem)
