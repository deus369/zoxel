// [none] Melee
extern ecs_entity_t spawn_pickup(ecs_world_t *world, const float3 position, const ecs_entity_t voxel);

void MeleeSystem(ecs_iter_t *it) {
    zox_field_world()
    zox_field_in(UserLink, userLinks, 1)
    zox_field_out(SkillActive, skillActives, 2)
    zox_field_in(SkillDamage, skillDamages, 3)
    zox_field_in(SkillRange, skillRanges, 4)
    for (int i = 0; i < it->count; i++) {
        zox_field_i(UserLink, userLinks, userLink)
        if (!zox_alive(userLink->value)) {
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
        const ecs_entity_t attacking_character = userLink->value;
        const RaycastVoxelData *raycastVoxelData = zox_get(attacking_character, RaycastVoxelData)
        // todo: reduce energy stat value using SkillCost, check if has enough energy
        const float skill_damage = skillDamage->value;
        const float skill_range = skillRange->value;
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
                        if (statValue->value < 0) {
                            statValue->value = 0;
                        }
                        else if (statValue->value > stat_value_max) {
                            statValue->value = stat_value_max;
                        }
                        zox_set(hit_character, LastDamager, { attacking_character })
                    }
                    spawn_sound_generated(world, instrument_violin, note_frequencies[28], 0.6, 2.4f);
                } else if (raycastVoxelData->voxel != 0 && raycastVoxelData->voxel_entity) {
                    raycast_action(world, raycastVoxelData, 0, 2);
                    if (zox_has(raycastVoxelData->chunk, TerrainChunk)) {
                        const ecs_entity_t pickup = spawn_pickup(world, raycastVoxelData->position_real, raycastVoxelData->voxel_entity);
                        const ecs_entity_t terrain = zox_get_value(raycastVoxelData->chunk, VoxLink)
                        if (terrain && zox_has(terrain, RealmLink)) {
                            const ecs_entity_t realm = zox_get_value(terrain, RealmLink)
                            const VoxelLinks *voxels = zox_get(realm, VoxelLinks)
                            const byte voxel_index = raycastVoxelData->voxel - 1;
                            const ecs_entity_t voxel = voxels->value[voxel_index];
                            // now get item and set to pickup
                            if (zox_has(voxel, ItemLink)) {
                                const ecs_entity_t item = zox_get_value(voxel, ItemLink)
                                if (item) zox_set(pickup, ItemLink, { item })
                            }
                            spawn_sound_generated(world, instrument_violin, note_frequencies[34], 0.6, 2.4f);
                        } else {
                            zox_log(" ! terrain is invalid\n")
                        }
                    } else {
                        zox_log(" ! cannot create pickup on non terrain chunk\n")
                    }
                    //zox_log(" > spawned pickup at [%fx%fx%f]\n", raycastVoxelData->position_real.x, raycastVoxelData->position_real.y, raycastVoxelData->position_real.z)
                } else {
                    // cannot hit air
                    spawn_sound_generated(world, instrument_violin, note_frequencies[44], 0.3, 2.4f);
                }
            }
        } else {
            // ray too far
            spawn_sound_generated(world, instrument_violin, note_frequencies[44], 0.3, 2.4f);
        }
    }
} zox_declare_system(MeleeSystem)