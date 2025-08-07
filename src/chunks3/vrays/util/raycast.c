// actually, we raycast character bounds and terrain seperately
//  todo: seperate character raycast from terrain, and we just compare them both
byte raycast_locks = 0;

typedef struct {
    entity e;
    float distance;
    float3 point;
    float3 normal;
} CharacterRaycast;

CharacterRaycast raycast_character(ecs *world,
    const float3 ray_origin,
    const float3 ray_normal,
    const entity caster,
    const EntityLinks* entities)
{
    CharacterRaycast ray = {
        .e = 0,
        .distance = FLT_MAX,
    };
    if (!entities) {
        return ray;
    }
    for (int i = 0; i < entities->length; i++) {
        const entity e = entities->value[i];
        if (!zox_valid(e) || caster == e || !zox_has(e, Position3D) || !zox_has(e, Bounds3D)) {
            continue;
        }
        zox_geter_value(e, Position3D, float3, position3)
        zox_geter_value(e, Rotation3D, float4, rotation3)
        zox_geter_value(e, Bounds3D, float3, bounds3)
        const bounds character_bounds = {
            .center = position3,
            .extents = calculate_aabb_extents(bounds3, rotation3)
        };
        float tmin, tmax;
        if (point_in_aabb(ray_origin, character_bounds)) {
            tmin = 0.0f;
            tmax = FLT_MAX;
        } else if (!ray_intersects_aabb(ray_origin, ray_normal, character_bounds, &tmin, &tmax)) {
            continue;
        }
        if (tmin < ray.distance) {
            ray.distance = tmin;
            // data->chunk = e;
            ray.point = float3_add(ray_origin, float3_scale(ray_normal, tmin));
            // data->normal = (int3) { 0, 0, 0 }; // You may want to calculate the actual normal at the intersection point
            ray.e = e;
        }
    }
    return ray;
}

byte raycast_voxel_node(
    ecs *world,
    const entity caster,
    const VoxelLinks *voxels,
    const ChunkLinks *chunk_links,
    int3 chunk_position,
    const float3 chunk_position_real,
    const int3 chunk_size,
    entity chunk,
    const float3 ray_origin,
    const float3 ray_normal,
    const float voxel_scale,
    const float ray_length,
    RaycastVoxelData *data,
    CharacterRaycast character_raycast)
{
    // setup voxel data
    const byte raycasting_terrain = voxels && voxels->length && chunk_links;
    const VoxelNode* node_chunk = NULL;
    VoxelNode* node_voxel = NULL;
    byte chunk_depth = 0;
    byte ray_hit = 0;
    float ray_distance = 0;
    int3 hit_normal = int3_zero;
    // CharacterRaycast character_raycast = { };
    byte was_hitting = 0;
    uint checks = 0;
    if (zox_valid(chunk)) {
        node_chunk = zox_get(chunk, VoxelNode);
        if (raycast_locks && node_chunk) {
            read_lock_VoxelNode(node_chunk);
        }
        chunk_depth = zox_get_value(chunk, NodeDepth);
        if (raycasting_terrain) {
            zox_geter(chunk, EntityLinks, entities)
            character_raycast = raycast_character(world,
                ray_origin,
                ray_normal,
                caster,
                entities);
        }
    }
    const byte3 chunk_size_b3 = int3_to_byte3(chunk_size);
    // position
    byte3 position_local;
    int3 position_global;
    byte3 voxel_position_local_last;
    int3 position_global_last;
    float3 position_real_last;
    entity chunk_last = chunk;
    VoxelNode *node_last = NULL;
    // zero for terrain raycasting
    float3 local_ray_origin = float3_subtract(ray_origin, chunk_position_real);
    position_global = real_position_to_voxel_position2(local_ray_origin, voxel_scale);
    const float3 ray_origin_scaled = float3_scale(local_ray_origin, 1.0f / voxel_scale); // get float voxel position
    // ray
    const int3 step_direction = float3_to_int3(float3_sign(ray_normal));
    const float3 ray_unit_size = (float3) { 1.0f / float_abs(ray_normal.x), 1.0f / float_abs(ray_normal.y), 1.0f / float_abs(ray_normal.z) };
    // get first difference
    float3 ray_add = float3_zero;
    if (ray_normal.x < 0) {
        ray_add.x = (ray_origin_scaled.x - position_global.x);
    } else {
        ray_add.x = ((float) position_global.x + 1 - ray_origin_scaled.x);
    }
    if (ray_normal.y < 0) {
        ray_add.y = (ray_origin_scaled.y - (float) position_global.y);
    } else {
        ray_add.y = ((float) position_global.y + 1 - ray_origin_scaled.y);
    }
    if (ray_normal.z < 0) {
        ray_add.z = (ray_origin_scaled.z - (float) position_global.z);
    } else {
        ray_add.z = ((float) position_global.z + 1 - ray_origin_scaled.z);
    }
    float3_scale3_p(&ray_add, ray_unit_size);
    while (ray_distance <= ray_length && checks < safety_checks_raycasting) {
        if (raycasting_terrain) {
            const int3 new_chunk_position = voxel_position_to_chunk_position(position_global, chunk_size);
            // Steps through chunks in our terrain!
            if (!int3_equals(chunk_position, new_chunk_position)) {
                if (raycast_locks && node_chunk) {
                    read_unlock_VoxelNode(node_chunk);
                }
                chunk = int3_hashmap_get(chunk_links->value, new_chunk_position);
                if (!zox_valid(chunk)) {
                    return 0;
                }
                node_chunk = zox_get(chunk, VoxelNode);
                if (!node_chunk) {
                    return 0;
                }
                if (raycast_locks) {
                    read_lock_VoxelNode(node_chunk);
                }
                chunk_depth = zox_get_value(chunk, NodeDepth)
                chunk_position = new_chunk_position;
                // only do this once when hitting a new chunk
                if (!character_raycast.e) {
                    zox_geter(chunk, EntityLinks, entities)
                    character_raycast = raycast_character(world,
                        ray_origin,
                        ray_normal,
                        caster,
                        entities);
                }
                /*if (!is_character_hit) {
                    zox_log(" 1 !!! Not Hit: vray[%f]", ray_distance)
                } else {
                    zox_log("2 ### Hit [%s]: cray [%f] < vray [%f]?", zox_get_name(data->chunk), closest_t, ray_distance)
                }*/
            }
            position_local = get_local_position_byte3(position_global, chunk_size_b3);
        } else {
            if (int3_in_bounds(position_global, chunk_size)) {
                position_local = int3_to_byte3(position_global);
                if (!was_hitting) {
                    was_hitting = 1;
                    // only do this once when hitting a new chunk
                    /*character_raycast = raycast_character(world,
                        ray_origin,
                        ray_normal,
                        caster,
                        entities);*/
                }
            } else {
                position_local = (byte3) { 255, 255, 255 }; // failure!
                // return here ?
                if (was_hitting) {
                    if (raycast_locks && node_chunk) {
                        read_unlock_VoxelNode(node_chunk);
                    }
                    return ray_hit_type_none;
                }
            }
        }

        // if didnt hit voxel, check from character hit
        if (character_raycast.e && character_raycast.distance <= ray_distance) {
            data->chunk = character_raycast.e;
            data->hit = character_raycast.point;
            data->distance = character_raycast.distance;
            data->normal = ray_normal;
            // data->hit = float3_add(ray_origin, float3_scale(ray_normal, ray_distance * voxel_scale));
            if (raycast_locks && node_chunk) {
                read_unlock_VoxelNode(node_chunk);
            }
            return ray_hit_type_character;
        }/*else {
            // zox_log("cp [%ix%ix%i]", new_chunk_position.x, new_chunk_position.y, new_chunk_position.z)
            //zox_log("vr [%f]  cr [%f]", ray_distance, character_raycast.distance)
        }*/

        byte hit_voxel = 0;
        byte is_in_bounds = byte3_in_bounds(position_local, chunk_size_b3);
        if (is_in_bounds) {
            byte3 temp = position_local;
            node_voxel = get_voxel_node_at_depth(&hit_voxel, node_chunk, &temp, chunk_depth);
        }
        if (is_in_bounds && hit_voxel) {
            if (!raycasting_terrain) {
                data->distance = ray_distance * voxel_scale;
                data->normal = int3_to_float3(hit_normal);
                // zox_log(" + hit minivox voxel; ray_distance [%f] voxel [%i] - depth [%i] x", ray_distance, hit_voxel, chunk_depth)
                // zox_log("  + at [%ix%ix%i]", position_local.x, position_local.y, position_local.z)
                if (raycast_locks && node_chunk) {
                    read_unlock_VoxelNode(node_chunk);
                }
                return ray_hit_type_block_vox;
            }
            // safety!
            if (hit_voxel - 1 >= voxels->length) {
                zox_logw("voxel index out of bounds [%i]", hit_voxel);
                if (raycast_locks && node_chunk) {
                    read_unlock_VoxelNode(node_chunk);
                }
                return ray_hit_type_none;
            }
            entity hit_block = voxels->value[hit_voxel - 1];
            if (raycasting_terrain) {
                data->hit_block = hit_block;
            }
            // check for minivoxes here
            byte is_minivox = is_minivox = zox_has(hit_block, BlockVox);
            if (!is_minivox) {
                ray_hit = ray_hit_type_terrain;
                // zox_log("vray [%f] cray [%f]", ray_distance, character_raycast.distance)
                /*if (!is_character_hit) {
                    zox_log(" 2 !!! Not Hit: vray[%f]", ray_distance)
                } else {
                    zox_log(" 2 ### Hit [%s]: cray [%f] < vray [%f]?", zox_get_name(data->chunk), closest_t, ray_distance)
                }*/
                break;
            }
            // is minivox!
            entity block_spawn = get_node_entity_VoxelNode(node_voxel);
            if (block_spawn && zox_has(block_spawn, Position3D)) {
                // positioning
                zox_geter_value_non_const(block_spawn, Position3D, float3, block_position)
                float3 ray_point = float3_add(ray_origin, float3_scale(ray_normal, ray_distance * voxel_scale));
                // remember: assuming centred, so make cornered position!
                // offset to corner, half block back! voxel_scale * 0.5
                float3_subtract_float3_p(&block_position, float3_single(voxel_scale * 0.5f));
                // model itself
                entity vox;
                // if Instanced mesh, use meta, otherwise use world block spawn!
                if (zox_has(block_spawn, InstanceLink)) {
                    vox = zox_get_value(block_spawn, InstanceLink)
                } else if (zox_has(hit_block, ModelLink)) {
                    // zox_log_error("does this happy anymore??")
                    vox = zox_get_value(hit_block,  ModelLink)
                } else {
                    vox = chunk;
                }
                if (!zox_valid(vox) || !zox_has(vox, NodeDepth)) {
                    if (zox_valid(vox)) {
                        zox_log_error("invalid vox selected [%s]", zox_get_name(vox));
                    } else {
                        zox_log_error("invalid vox selected");
                    }
                    if (raycast_locks && node_chunk) {
                        read_unlock_VoxelNode(node_chunk);
                    }
                    return ray_hit_type_none;
                }
                const byte node_depth = zox_get_value(vox, NodeDepth)
                int chunk_length = powers_of_two[node_depth];
                float new_voxel_scale = voxel_scale * (1.0f / (float) chunk_length);
                // zox_log("> raycasting minivox: hit_voxel [%i], chunk_length: %i - %f  - %fx%fx%f", hit_voxel, chunk_size.x, new_voxel_scale, block_position.x, block_position.y, block_position.z)
                byte result = raycast_voxel_node(world,
                    caster,
                    NULL,
                    NULL,
                    int3_zero,
                    block_position,
                    int3_single(chunk_length),
                    vox,
                    ray_point,
                    ray_normal,
                    new_voxel_scale,
                    chunk_length * 2,
                    data,
                    character_raycast);
                if (result == ray_hit_type_block_vox) {
                    ray_hit = ray_hit_type_block_vox;
                    data->distance += ray_distance * voxel_scale;
                    // zox_log("   - Hitting Block Vox, Sub Vox")
                    break;
                } else if (result == ray_hit_type_character) {
                    // no need to set more stuff here
                    //  data->hit set by child process
                    //  data->distance set by child process
                    data->distance += ray_distance * voxel_scale;
                    data->hit = float3_add(ray_origin, float3_scale(ray_normal, data->distance));
                    // zox_log("+ hit npc through grass [%f]", data->distance)
                    if (raycast_locks && node_chunk) {
                        read_unlock_VoxelNode(node_chunk);
                    }
                    return ray_hit_type_character;
                } /*else {
                    zox_log("Passing through: %s in minivox", result == ray_hit_type_none ? "air" : "idk")
                }*/
            }
        }

        // Traverse the grid with DDA
        if (ray_add.x < ray_add.y && ray_add.x < ray_add.z) {
            ray_distance = ray_add.x;
            position_global.x += step_direction.x;
            ray_add.x += ray_unit_size.x;
            if (step_direction.x >= 0) {
                hit_normal = int3_left;
            } else {
                hit_normal = int3_right;
            }
        } else if (ray_add.y < ray_add.z) {
            ray_distance = ray_add.y;
            position_global.y += step_direction.y;
            ray_add.y += ray_unit_size.y;
            if (step_direction.y >= 0) {
                hit_normal = int3_down;
            } else {
                hit_normal = int3_up;
            }
        } else {
            ray_distance = ray_add.z;
            position_global.z += step_direction.z;
            ray_add.z += ray_unit_size.z;
            if (step_direction.z >= 0) {
                hit_normal = int3_backward;
            } else {
                hit_normal = int3_forward;
            }
        }
        // caches
        voxel_position_local_last = position_local;
        position_global_last = position_global;
        position_real_last = voxel_to_real_position(position_local, chunk_position, chunk_size_b3, voxel_scale);
        chunk_last = chunk;
        node_last = node_voxel;
        checks++; // safety first
    }
    /*if (ray_hit == ray_hit_type_block_vox && !raycasting_terrain) {
        data->distance = ray_distance;
        data->normal = int3_to_float3(hit_normal);
    } else */

    if (ray_hit == ray_hit_type_terrain ||
        (ray_hit == ray_hit_type_block_vox && raycasting_terrain))
    {
        if (ray_hit == ray_hit_type_terrain) {
            data->distance = ray_distance * voxel_scale;
            data->normal = int3_to_float3(hit_normal);
        }
        // calculate our point off the distance
        data->hit = float3_add(ray_origin, float3_scale(ray_normal, data->distance));
        // calculate real position off voxel one
        float3 voxel_position_real = float3_scale(int3_to_float3(position_global), voxel_scale);
        float3_add_float3_p(&voxel_position_real, (float3) { voxel_scale / 2.0f, voxel_scale / 2.0f, voxel_scale / 2.0f }); // add half voxel
        float3_add_float3_p(&voxel_position_real, chunk_position_real);
        data->position = position_local;
        data->position_global = position_global;
        data->position_real = voxel_to_real_position(position_local, chunk_position, chunk_size_b3, voxel_scale);
        data->voxel_scale = voxel_scale;
        data->chunk = chunk;
        data->position_last = voxel_position_local_last;
        data->position_global_last = position_global_last;
        data->position_real_last = position_real_last;
        data->chunk_last = chunk_last;
        data->node = node_voxel;
        data->voxel = node_voxel->value;
        data->node_last = node_last;
#if zox_debug_hit_point
        const color_rgb hit_point_line_color = (color_rgb) { 0, 255, 255 };
        render_line3D(world, data->hit, float3_add(data->hit, float3_scale(int3_to_float3(hit_normal), voxel_scale * get_terrain_voxel_scale(node_depth))), hit_point_line_color);
#endif
#ifdef zox_debug_hit_normal
        const color_rgb voxel_line_color  = (color_rgb) { 0, 0, 0 };
        render_line3D(world, voxel_position_real, float3_add(voxel_position_real, float3_scale(int3_to_float3(hit_normal), voxel_scale)), voxel_line_color);
#endif
    } else if (ray_hit == ray_hit_type_none) {
        data->chunk = 0;
        data->position = byte3_zero;
        data->position_global = int3_zero;
        data->normal = float3_zero;
        data->hit = float3_zero;
        data->position_real = float3_zero;
        data->position_last = byte3_zero;
        data->position_global_last = int3_zero;
        data->position_real_last = float3_zero;
        data->chunk_last = 0;
        data->node_last = NULL;
    }
    if (raycast_locks && node_chunk) {
        read_unlock_VoxelNode(node_chunk);
    }
    return ray_hit;
}