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
        if (action_selected == 255) {
            triggerActionB->value = 0;
            continue; // no actionbar
        }
        if (action_selected >= actionLinks->length) {
            zox_log(" > action selected is out of bounds\n")
            triggerActionB->value = 0;
            continue;
        }
        const ecs_entity_t action_entity = actionLinks->value[action_selected];
        // no action assigned
        if (!action_entity) {
            triggerActionB->value = 0;
            continue;
        }
        if (zox_has(action_entity, ItemBlock)) {
            const ecs_entity_t block = zox_get_value(action_entity, BlockLink)
            if (block) {
                const unsigned char block_index = zox_get_value(block, BlockIndex)
                raycast_action(world, raycastVoxelData, block_index, 1);
            }
        } else if (zox_has(action_entity, Skill)) {
            // zox_log(" > toggling skill [%s]\n", zox_get_name(action_entity))
            if (zox_has(action_entity, Aura)) {
                zox_set(action_entity, SkillActive, { !zox_gett_value(action_entity, SkillActive) })
            } else if (zox_has(action_entity, Melee)) {
                // todo: reduce energy stat value using SkillCost, check if has enough energy
                const float skill_damage = zox_get_value(action_entity, SkillDamage)
                const float skill_range = zox_get_value(action_entity, SkillRange)
                if (raycastVoxelData->distance <= skill_range) {
                    // zox_log(" > activating melee skill [%s]\n", zox_get_name(action_entity))
                    if (raycastVoxelData->chunk) {
                        if (zox_has(raycastVoxelData->chunk, Character3D)) {
                            const ecs_entity_t hit_character = raycastVoxelData->chunk;
                            const StatLinks *hit_character_stats = zox_get(hit_character, StatLinks)
                            find_array_component_with_tag(hit_character_stats, HealthStat, health_stat)
                            if (!health_stat) {
                                zox_log(" ! user had no health\n")
                                continue;
                            } else {
                                const float stat_value_max = zox_get_value(health_stat, StatValueMax)
                                zox_get_muter(health_stat, StatValue, statValue)
                                statValue->value += skill_damage;
                                if (statValue->value < 0) statValue->value = 0;
                                else if (statValue->value > stat_value_max) statValue->value = stat_value_max;
                                zox_set(hit_character, LastDamager, { e })
                            }
                        } else {
                            raycast_action(world, raycastVoxelData, 0, 2);
                            // zox_log(" > spawned pickup at [%fx%fx%f]\n", raycastVoxelData->position_real.x, raycastVoxelData->position_real.y, raycastVoxelData->position_real.z)
                            spawn_pickup(world, prefab_pickup, raycastVoxelData->position_real);
                        }
                        spawn_sound_generated(world, instrument_violin, note_frequencies[34], 0.6, 2.4f);
                    }
                } else {
                    // ray too far
                    spawn_sound_generated(world, instrument_violin, note_frequencies[44], 0.3, 2.4f);
                }
            } else {
                zox_log(" > skill not actionable yet [%s]\n", zox_get_name(action_entity))
            }

        } else {
            zox_log(" > action entity is not a block item\n")
        }
        triggerActionB->value = 0;
    }
} zox_declare_system(PlayerPlaceVoxelSystem)
