// [none] Melee
extern ecs_entity_t spawn_pickup_block(ecs_world_t*, const float3, const ecs_entity_t);

void MeleeSystem(ecs_iter_t *it) {
    const float popup_spawn_y = 0.18f;
    const double volume = get_volume_sfx();
    zox_sys_world()
    zox_sys_begin()
    zox_sys_in(UserLink)
    zox_sys_in(SkillDamage)
    zox_sys_in(SkillDamageMax)
    zox_sys_in(SkillRange)
    zox_sys_in(SkillResourceLink)
    zox_sys_in(SkillCost)
    zox_sys_out(SkillActive)    // use state systems
    for (int i = 0; i < it->count; i++) {
        zox_sys_i(UserLink, userLink)
        zox_sys_i(SkillDamage, skillDamage)
        zox_sys_i(SkillDamageMax, skillDamageMax)
        zox_sys_i(SkillRange, skillRange)
        zox_sys_i(SkillResourceLink, skillResourceLink)
        zox_sys_i(SkillCost, skillCost)
        zox_sys_o(SkillActive, skillActive)
        const ecs_entity_t user = userLink->value;
        if (!skillActive->value) {
            continue;
        }
        skillActive->value = 0;

        // user validation
        if (!zox_valid(user) || !zox_has(user, StatLinks) || zox_gett_value(user, Dead)) {
            continue;
        }

        // does have skillResourceLink
        ecs_entity_t resource = 0;
        ecs_entity_t strength = 0;
        zox_geter(user, StatLinks, stats)
        for (int j = 0; j < stats->length; j++) {
            const ecs_entity_t stat = stats->value[j];
            zox_get_prefab(stat, stat_parent)
            if (skillResourceLink->value == stat_parent) {
                resource = stat;
            }
            if (!strength && zox_has(stat, StatAttribute)) {
                strength = stat;
            }
        }
        // todo: move cost use into activation system
        if (!resource || !zox_has(resource, StatValue)) {
            continue;
        }

        // resource cost
        float resource_left = zox_get_value(resource, StatValue)
        if (resource_left < skillCost->value) {
            continue;
        }
        // this should be muter -> instant use
        zox_set(resource, StatValue, { resource_left - skillCost->value })


        // skill validation
        if (skillRange->value == 0) {
            // play sound!
            spawn_sound_generated(world, prefab_sound_generated, instrument_violin, note_frequencies[44], 0.3, volume);
            continue;
        }
        zox_geter(user, RaycastVoxelData,  raycastVoxelData)

        // todo: reduce energy stat value using SkillCost, check if has enough energy
        float skill_damage = randf_range(skillDamage->value, skillDamageMax->value);
        if (strength) {
            skill_damage += 3 * zox_gett_value(strength, StatValue);
        }

        const float skill_range = skillRange->value;
        const ecs_entity_t hit = raycastVoxelData->chunk;
        const byte in_range = raycastVoxelData->distance <= skill_range;
        if (!hit || !in_range) {
            // ray too far
            spawn_sound_generated(world, prefab_sound_generated, instrument_violin, note_frequencies[44], 0.3, volume);
            continue;
        }
        // zox_log(" > activating melee skill [%s]\n", zox_get_name(action_entity))
        if (zox_has(hit, Character3)) {
            // const ecs_entity_t hit_character = hit;
            zox_geter(hit, StatLinks, hit_stats)
            find_array_component_with_tag(hit_stats, HealthStat, health_stat)
            if (!health_stat) {
                zox_log_error("hit user had no health")
                continue;
            } else {
                const float stat_value_max = zox_get_value(health_stat, StatValueMax)
                zox_get_muter(health_stat, StatValue, statValue)
                statValue->value -= skill_damage;
                if (statValue->value < 0) {
                    statValue->value = 0;
                } else if (statValue->value > stat_value_max) {
                    statValue->value = stat_value_max;
                }
                // zox_log("[%s] took [%f] damage and is on [%f] health", zox_get_name(hit), skill_damage, statValue->value)
                // zox_set(hit, LastDamager, { user })
                combat_on_hit(world, hit, user);
            }

            // add knockback
            float3 hit_impulse = float3_scale(raycastVoxelData->normal, randf_range(knockback_min, knockback_max));
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

                // effect our terrain here
                raycast_action(world, raycastVoxelData, 0, 2);

                // destroy voxel sound
                spawn_sound_generated(world, prefab_sound_generated, instrument_piano, note_frequencies[24 + rand() % 6], 0.4, 1.2f * get_volume_sfx());

                // todo: spawn pickup in VoxelNodeDirty system - TerrainItemDropSystem
                // this requires a stack on chunk for its updates

                // spawn a pickup if removed
                if (zox_has(hit, TerrainChunk)) {
                    const ecs_entity_t pickup = spawn_pickup_block(world, raycastVoxelData->position_real, raycastVoxelData->hit_block);
                    const ecs_entity_t block = raycastVoxelData->hit_block; // voxel;
                    // now get item and set to pickup
                    if (zox_valid(block) && zox_has(block, ItemLink)) {
                        const ecs_entity_t item = zox_get_value(block, ItemLink)
                        if (item) {
                            zox_set(pickup, ItemLink, { item })
                        }
                    }
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