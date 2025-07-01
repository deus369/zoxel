// left click - destroy
#ifdef zox_mod_actions
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
        if (raycastVoxelData->voxel_entity) {
            raycast_action(world, raycastVoxelData, 0, 2);
            spawn_pickup(world, raycastVoxelData->hit, raycastVoxelData->voxel_entity);
        }
        triggerActionA->value = 0;
    }
} zox_declare_system(VoxelActionASystem)
#endif