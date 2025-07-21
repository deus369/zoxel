// [none] Melee
extern ecs_entity_t spawn_pickup(ecs_world_t *world, const float3 position, const ecs_entity_t voxel);

float randf() {
    return (float)rand() / (float)RAND_MAX;
}

float randf_range(float min, float max) {
    return min + (max - min) * randf();
}

void MeleeSystem(ecs_iter_t *it) {
    const float popup_spawn_y = 0.18f;
    const double volume = get_volume_sfx();
    zox_sys_world()
    zox_sys_begin()
    zox_sys_in(UserLink)
    zox_sys_in(SkillDamage)
    zox_sys_in(SkillDamageMax)
    zox_sys_in(SkillRange)
    zox_sys_in(SkillCost)
    zox_sys_out(SkillActive)    // use state systems
    for (int i = 0; i < it->count; i++) {
        zox_sys_i(UserLink, userLink)
        zox_sys_i(SkillDamage, skillDamage)
        zox_sys_i(SkillDamageMax, skillDamageMax)
        zox_sys_i(SkillRange, skillRange)
        zox_sys_i(SkillCost, skillCost)
        zox_sys_o(SkillActive, skillActive)
        const ecs_entity_t user = userLink->value;
        if (!skillActive->value) {
            continue;
        }
        skillActive->value = 0;
        // user validation
        if (!zox_valid(user) || !zox_has(user, StatLinks) && !zox_gett_value(user, Dead)) {
            continue;
        }
        zox_geter(user, StatLinks, stats)
        if (stats->length < 4) {
            continue;
        }
        // todo: move cost use into activation system
        const ecs_entity_t energy = stats->value[3];
        if (!energy || !zox_has(energy, StatValue)) {
            continue;
        }
        // resource cost
        float energy_value = zox_get_value(energy, StatValue)
        if (energy_value < skillCost->value) {
            continue;
        }
        zox_set(energy, StatValue, { energy_value - skillCost->value })
        // skill validation
        if (skillRange->value == 0) {
            // play sound!
            spawn_sound_generated(world, prefab_sound_generated, instrument_violin, note_frequencies[44], 0.3, volume);
            continue;
        }
        zox_geter(user, RaycastVoxelData,  raycastVoxelData)
        // todo: reduce energy stat value using SkillCost, check if has enough energy
        const float skill_damage =  randf_range(skillDamage->value, skillDamageMax->value);
        const float skill_range = skillRange->value;
        const ecs_entity_t hit = raycastVoxelData->chunk;
        const byte in_range = raycastVoxelData->distance <= skill_range;
        if (!hit || !in_range) {
            // ray too far
            spawn_sound_generated(world, prefab_sound_generated, instrument_violin, note_frequencies[44], 0.3, volume);
            continue;
        }
        // zox_log(" > activating melee skill [%s]\n", zox_get_name(action_entity))
        if (zox_has(hit, Character3D)) {
            const ecs_entity_t hit_character = hit;

            zox_geter(hit, StatLinks, hit_stats)
            find_array_component_with_tag(hit_stats, HealthStat, health_stat)
            if (!health_stat) {
                zox_log_error("hit user had no health")
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
                zox_set(hit, LastDamager, { user })
            }

            // add knockback
            float3 hit_impulse = float3_scale(raycastVoxelData->normal, randf_range(1.5f, 3.0f));
            zox_muter(hit, Velocity3D, hit_velocity)
            hit_velocity->value = float3_add(hit_velocity->value, hit_impulse);
            // zox_log("+ added impulse [%fx%fx%f]", hit_impulse.x, hit_impulse.y, hit_impulse.z)

            // hit sound
            spawn_sound_generated(world, prefab_sound_generated, instrument_violin, note_frequencies[28], 0.6, volume);

            // damage popup
            const float3 bounds3D = zox_get_value(hit, Bounds3D)
            const float3 hit_character_position = zox_get_value(hit, Position3D)
            const float3 popup_position = (float3) { hit_character_position.x, hit_character_position.y + bounds3D.y + popup_spawn_y, hit_character_position.z };
            char popup_text[64];
            sprintf(popup_text, "%i", (int) floor(skill_damage));
            const color popup_color = (color) { 255, 0, 0, 255 };
            spawn_popup3_easy(world, popup_text, popup_color, popup_position, 2.5f, 4 + rand() % 4);

        } else if (raycastVoxelData->voxel != 0 && raycastVoxelData->hit_block) {
            if (!zox_has(raycastVoxelData->hit_block, BlockInvinsible)) {
                raycast_action(world, raycastVoxelData, 0, 2);
                if (zox_has(hit, TerrainChunk)) {
                    const ecs_entity_t pickup = spawn_pickup(world, raycastVoxelData->position_real, raycastVoxelData->hit_block);
                    const ecs_entity_t terrain = zox_get_value(hit, VoxLink)
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
                        // destroy voxel sound
                        spawn_sound_generated(world, prefab_sound_generated, instrument_piano, note_frequencies[24 + rand() % 6], 0.4, 1.2f * get_volume_sfx());
                    } else {
                        zox_log_error("hit terrain is invalid")
                    }
                } else {
                    zox_log_error("cannot create pickup on non terrain chunk")
                }
            } else {
                // cannot destroy voxel sound
                spawn_sound_generated(world, prefab_sound_generated, instrument_violin, note_frequencies[42 + rand() % 6], 0.26, 1.4f * get_volume_sfx());
            }
        } else {
            // cannot hit air
            spawn_sound_generated(world, prefab_sound_generated, instrument_violin, note_frequencies[44], 0.3, volume);
        }
    }
} zox_declare_system(MeleeSystem)