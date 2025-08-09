// left click - destroy
/*void VoxelActionASystem(ecs_iter_t *it) {
    zox_sys_world()
    zox_sys_begin()
    zox_sys_in(RaycastVoxelData)
    zox_sys_out(TriggerActionA)
    for (int i = 0; i < it->count; i++) {
        zox_sys_o(TriggerActionA, triggerActionA)
        zox_sys_i(RaycastVoxelData, raycastVoxelData)
        if (!triggerActionA->value) {
            continue;
        }
        if (raycastVoxelData->hit_block && !zox_has(raycastVoxelData->hit_block, BlockInvinsible)) {
            raycast_action(world, raycastVoxelData, 0, 2);
            spawn_pickup_block(world, raycastVoxelData->hit, raycastVoxelData->hit_block);
        }
        triggerActionA->value = 0;
    }
} zoxd_system(VoxelActionASystem)*/