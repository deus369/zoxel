// [none] Melee
extern ecs_entity_t spawn_pickup(ecs_world_t *world, const float3 position, const ecs_entity_t voxel);

void MeleeSystem(ecs_iter_t *it) {
    const double volume = global_volume_sfx;
    zox_field_world()
    zox_field_in(UserLink, userLinks, 1)
    zox_field_out(SkillActive, skillActives, 2)
    zox_field_in(SkillDamage, skillDamages, 3)
    zox_field_in(SkillRange, skillRanges, 4)
    zox_field_in(SkillCost, skillCosts, 5)
    for (int i = 0; i < it->count; i++) {
        zox_field_i(UserLink, userLinks, userLink)
        const ecs_entity_t attacking_character = userLink->value;
        if (!zox_alive(attacking_character) || !zox_has(attacking_character, StatLinks)) {
            continue;
        }
        zox_field_o(SkillActive, skillActives, skillActive)
        if (!skillActive->value) {
            continue;
        }
        skillActive->value = 0;

        zox_field_i(SkillDamage, skillDamages, skillDamage)
        if (skillDamage->value == 0) {
            continue;
        }
        zox_field_i(SkillRange, skillRanges, skillRange)
        if (skillRange->value == 0) {
            continue;
        }

        // todo: move cost use into activation system
        zox_field_i(SkillCost, skillCosts, skillCost)
        zox_geter(attacking_character, StatLinks, stats)
        if (stats->length < 4) {
            continue;
        }
        const ecs_entity_t energy = stats->value[3];
        if (!energy || !zox_has(energy, StatValue)) {
            continue;
        }
        float energy_value = zox_get_value(energy, StatValue)
        if (energy_value < skillCost->value) {
            continue;
        }
        zox_set(energy, StatValue, { energy_value - skillCost->value })

        const RaycastVoxelData *raycastVoxelData = zox_get(attacking_character, RaycastVoxelData)
        // todo: reduce energy stat value using SkillCost, check if has enough energy
        const float skill_damage = skillDamage->value;
        const float skill_range = skillRange->value;
        if (raycastVoxelData->distance <= skill_range) {
            // zox_log(" > activating melee skill [%s]\n", zox_get_name(action_entity))
            const ecs_entity_t hit_chunk = raycastVoxelData->chunk;
            if (hit_chunk) {
                if (zox_has(hit_chunk, Character3D)) {
                    const ecs_entity_t hit_character = hit_chunk;
                    zox_geter(hit_character, StatLinks, hit_character_stats)
                    find_array_component_with_tag(hit_character_stats, HealthStat, health_stat)
                    if (!health_stat) {
                        zox_log(" ! user had no health\n")
                        continue;
                    } else {
                        const float stat_value_max = zox_get_value(health_stat, StatValueMax)
                        zox_get_muter(health_stat, StatValue, statValue)
                        statValue->value += skill_damage;
                        if (statValue->value < 0) {
                            statValue->value = 0;
                        }
                        else if (statValue->value > stat_value_max) {
                            statValue->value = stat_value_max;
                        }
                        zox_set(hit_character, LastDamager, { attacking_character })
                    }
                    spawn_sound_generated(world, prefab_sound_generated, instrument_violin, note_frequencies[28], 0.6, volume);
                    // damage popup

                    const float3 hit_character_position = zox_get_value(hit_character, Position3D)
                    const float3 popup_position = (float3) { hit_character_position.x, hit_character_position.y + 0.26f, hit_character_position.z };
                    char popup_text[64];
                    sprintf(popup_text, "%i", (int) floor(skill_damage));
                    const color popup_color = (color) { 255, 0, 0, 255 };
                    spawn_popup3D_easy(world, popup_text, popup_color, popup_position);
                } else if (raycastVoxelData->voxel != 0 && raycastVoxelData->voxel_entity) {
                    raycast_action(world, raycastVoxelData, 0, 2);
                    if (zox_has(hit_chunk, TerrainChunk)) {
                        const ecs_entity_t pickup = spawn_pickup(world, raycastVoxelData->position_real, raycastVoxelData->voxel_entity);
                        const ecs_entity_t terrain = zox_get_value(hit_chunk, VoxLink)
                        if (terrain && zox_has(terrain, RealmLink)) {
                            const ecs_entity_t realm = zox_get_value(terrain, RealmLink)
                            const VoxelLinks *voxels = zox_get(realm, VoxelLinks)
                            const byte voxel_index = raycastVoxelData->voxel - 1;
                            const ecs_entity_t voxel = voxels->value[voxel_index];
                            // now get item and set to pickup
                            if (zox_has(voxel, ItemLink)) {
                                const ecs_entity_t item = zox_get_value(voxel, ItemLink)
                                if (item) {
                                    zox_set(pickup, ItemLink, { item })
                                }
                            }
                            spawn_sound_generated(world, prefab_sound_generated, instrument_violin, note_frequencies[34], 0.6, volume);
                        } else {
                            zox_log_error("terrain is invalid")
                        }
                    } else {
                        zox_log_error("cannot create pickup on non terrain chunk")
                    }
                } else {
                    // cannot hit air
                    spawn_sound_generated(world, prefab_sound_generated, instrument_violin, note_frequencies[44], 0.3, volume);
                }
            }
        } else {
            // ray too far
            spawn_sound_generated(world, prefab_sound_generated, instrument_violin, note_frequencies[44], 0.3, volume);
        }
    }
} zox_declare_system(MeleeSystem)