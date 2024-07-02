// right click = place
void PlayerPlaceVoxelSystem(ecs_iter_t *it) {
#ifdef zox_disable_raycasts3D
    return;
#endif
    // get held action type
    zox_iter_world()
    zox_field_in(RaycastVoxelData, raycastVoxelDatas, 1)
    zox_field_out(ActionLinks, actionLinkss, 2)
    zox_field_out(TriggerActionB, triggerActionBs, 3)
    for (int i = 0; i < it->count; i++) {
        zox_field_o(TriggerActionB, triggerActionBs, triggerActionB)
        if (!triggerActionB->value) continue;
        zox_field_i(RaycastVoxelData, raycastVoxelDatas, raycastVoxelData)
        zox_field_i(ActionLinks, actionLinkss, actionLinks)
        zox_field_e()
        const ecs_entity_t player = zox_get_value(e, PlayerLink)
        const unsigned char action_selected = get_player_action_index(world, player);
        if (action_selected >= actionLinks->length) {
            zox_log(" > action selected is out of bounds\n")
            triggerActionB->value = 0;
            continue;
        }
        const ecs_entity_t action_entity = actionLinks->value[action_selected];
        if (!action_entity) {
            triggerActionB->value = 0;
            continue;
        }
        if (!zox_has(action_entity, ItemBlock)) {
            zox_log(" > action entity is not a block item\n")
            triggerActionB->value = 0;
            continue;
        }
        const ecs_entity_t block = zox_get_value(action_entity, BlockLink)
        if (!block) {
            zox_log(" ! block from item is not valid\n")
            triggerActionB->value = 0;
            continue;
        }
        const unsigned char block_index = zox_get_value(block, BlockIndex)
        // get BlockLink
        raycast_action(world, raycastVoxelData, block_index, 1);
        triggerActionB->value = 0;
    }
} zox_declare_system(PlayerPlaceVoxelSystem)
