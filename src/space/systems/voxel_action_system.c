#ifdef zox_mod_actions

// left click - destroy
void VoxelActionASystem(ecs_iter_t *it) {
    zox_field_world()
    zox_field_in(RaycastVoxelData, raycastVoxelDatas, 1)
    zox_field_out(TriggerActionA, triggerActionAs, 2)
    for (int i = 0; i < it->count; i++) {
        zox_field_o(TriggerActionA, triggerActionAs, triggerActionA)
        if (!triggerActionA->value) {
            continue;
        }
        zox_field_i(RaycastVoxelData, raycastVoxelDatas, raycastVoxelData)
        if (raycastVoxelData->hit_block && !zox_has(raycastVoxelData->hit_block, BlockInvinsible)) {
            raycast_action(world, raycastVoxelData, 0, 2);
            spawn_pickup(world, raycastVoxelData->hit, raycastVoxelData->hit_block);
        }
        triggerActionA->value = 0;
    }
} zox_declare_system(VoxelActionASystem)

#endif