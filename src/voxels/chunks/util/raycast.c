byte is_raycast_minivoxes = 0;  // its broken atm

byte raycast_character(ecs_world_t *world, const ecs_entity_t caster, const float3 ray_origin, const float3 ray_normal, const ecs_entity_t chunk, RaycastVoxelData *data, float *closest_t) {
    if (!zox_valid(chunk) || !zox_has(chunk, EntityLinks)) {
        return 0;
    }
    byte hit_character = 0;
    zox_geter(chunk, EntityLinks, entity_links)
    *closest_t = FLT_MAX;
    for (int i = 0; i < entity_links->length; i++) {
        const ecs_entity_t character = entity_links->value[i];
        if (!character || !zox_valid(character) || caster == character || !zox_has(character, Position3D) || !zox_has(character, Bounds3D)) {
            continue;
        }
        const float3 position3D = zox_get_value(character, Position3D)
        const float3 bounds3D = zox_get_value(character, Bounds3D)
        const bounds character_bounds = { .center = position3D, .extents = bounds3D };
        float tmin, tmax;
        if (ray_intersects_aabb(ray_origin, ray_normal, character_bounds, &tmin, &tmax)) {
            if (tmin < *closest_t) {
                *closest_t = tmin;
                data->chunk = character;
                data->hit = float3_add(ray_origin, float3_multiply_float(ray_normal, tmin));
                // data->normal = (int3) { 0, 0, 0 }; // You may want to calculate the actual normal at the intersection point
                hit_character = 1;
            }
        }
    }
    return hit_character;
}

byte raycast_general(ecs_world_t *world, const ecs_entity_t caster, const VoxelLinks *voxels, const ChunkLinks *chunk_links, int3 chunk_position, const float3 chunk_position_real, const int3 chunk_size, ecs_entity_t chunk, const float3 ray_origin, const float3 ray_normal, const float voxel_scale, const float ray_length, RaycastVoxelData *data) {
    // setup voxel data
    const ChunkOctree *node;
    byte chunk_depth;
    if (chunk) {
        node = zox_get(chunk, ChunkOctree)
        chunk_depth = node->linked;
    }
    const byte3 chunk_size_b3 = int3_to_byte3(chunk_size);
    // position
    byte3 position_local;
    int3 position_global;
    byte3 voxel_position_local_last;
    int3 position_global_last;
    float3 position_real_last;
    ecs_entity_t chunk_last = chunk;
    ChunkOctree *node_last = NULL;
    // zero for terrain raycasting
    float3 local_ray_origin = float3_sub(ray_origin, chunk_position_real);
    position_global = real_position_to_voxel_position2(local_ray_origin, voxel_scale);
    const float3 ray_origin_scaled = float3_multiply_float(local_ray_origin, 1.0f / voxel_scale); // get float voxel position
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
    float3_multiply_float3_p(&ray_add, ray_unit_size);
    byte ray_hit = 0;
    int3 hit_normal = int3_zero;
    float ray_distance = 0;
    float closest_t;
    byte hit_character = 0;
    uint checks = 0;
    while (ray_distance <= ray_length && checks < safety_checks_raycasting) {
        if (chunk_links) {
            const int3 new_chunk_position = voxel_position_to_chunk_position(position_global, chunk_size);
            if (!int3_equals(chunk_position, new_chunk_position)) {
                chunk = int3_hashmap_get(chunk_links->value, new_chunk_position);
                if (!zox_valid(chunk)) {
                    return 0;
                }
                node = zox_get(chunk, ChunkOctree)
                if (!node) {
                    return 0;
                }
                chunk_depth = node->linked;
                chunk_position = new_chunk_position;
                hit_character = raycast_character(world, caster, ray_origin, ray_normal, chunk, data, &closest_t);
            }
        }
        if (chunk_links) {
            position_local = get_local_position_byte3(position_global, chunk_position, chunk_size_b3);
        } else {
            if (int3_in_bounds(position_global, chunk_size)) {
                position_local = int3_to_byte3(position_global);
            } else {
                position_local = (byte3) { 255, 255, 255 }; // failure!
            }
        }
        byte old_voxel = 0;
        if (byte3_in_bounds(position_local, chunk_size_b3)) {
            byte3 temp = position_local;
            data->node = get_voxel_node_at_depth(&old_voxel, node, &temp, chunk_depth);
        }
        if (old_voxel) {
            data->voxel = old_voxel;
            data->voxel_entity = voxels->value[old_voxel - 1];
            byte is_minivox = 0;
            if (is_raycast_minivoxes) {
                if (voxels) {
                    const ecs_entity_t block = voxels->value[old_voxel - 1];
                    is_minivox = zox_has(block, BlockVox);
                }
                if (is_minivox) {
                    ecs_entity_t block_spawn = get_node_entity_ChunkOctree(node);
                    if (block_spawn && zox_has(block_spawn,  Position3D)) {
                        float3 ray_point = float3_add(ray_origin, float3_multiply_float(ray_normal, ray_distance * voxel_scale));
                        float3 block_position = zox_get_value(block_spawn, Position3D)
                        // remember: assuming centred, so make cornered position!
                        float3_subtract_float3_p(&block_position, (float3) { 0.5f * voxel_scale, 0.5f * voxel_scale, 0.5f * voxel_scale }); // offset to corner, half block back!
                        const int3 chunk_size = zox_get_value(block_spawn, ChunkSize)
                        float new_voxel_scale = voxel_scale * (1.0f / (float) chunk_size.x);
                        if (raycast_general(world, 0, NULL, NULL, int3_zero, block_position, chunk_size, block_spawn, ray_point, ray_normal, new_voxel_scale, chunk_size.x, data)) {
                            ray_hit = 2;
                            chunk = block_spawn; // set hit chunk
                            break;
                        }
                    }
                }
            } else { // if solid block
                ray_hit = 1;
                // if (!chunk_links) zox_log(" > [%f] raycasted minivox [%ix%ix%i]\n", ray_distance, position_global.x, position_global.y, position_global.z)
                break;
            }
        }
        // if didnt hit voxel, check from character hit
        if (hit_character && closest_t < ray_distance) {
            ray_distance = closest_t;
            ray_hit = ray_hit_type_character; // Differentiate between voxel and character hit
            break;
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
        node_last = data->node;
        checks++; // safety first
    }
    data->distance = ray_distance;
    if (ray_hit == ray_hit_type_block_vox) {
        // we performed gizmo on recursive function call
    } else if (ray_hit == ray_hit_type_character) {
        data->hit = float3_add(ray_origin, float3_multiply_float(ray_normal, ray_distance * voxel_scale));
        //return ray_hit;
    } else if (ray_hit == ray_hit_type_terrain) {
        data->hit = float3_add(ray_origin, float3_multiply_float(ray_normal, ray_distance * voxel_scale));
        // hit point
#if zox_debug_hit_point
        const color_rgb hit_point_line_color = (color_rgb) { 0, 255, 255 };
        render_line3D(world, data->hit, float3_add(data->hit, float3_multiply_float(int3_to_float3(hit_normal), voxel_scale * get_terrain_voxel_scale(node->linked))), hit_point_line_color);
#endif
        // voxel normal
        float3 voxel_position_real = float3_multiply_float(int3_to_float3(position_global), voxel_scale);
        float3_add_float3_p(&voxel_position_real, (float3) { voxel_scale / 2.0f, voxel_scale / 2.0f, voxel_scale / 2.0f }); // add half voxel
        float3_add_float3_p(&voxel_position_real, chunk_position_real);
#ifdef zox_debug_hit_normal
        const color_rgb voxel_line_color  = (color_rgb) { 0, 0, 0 };
        render_line3D(world, voxel_position_real, float3_add(voxel_position_real, float3_multiply_float(int3_to_float3(hit_normal), voxel_scale)), voxel_line_color);
#endif
        // output chunk!
        data->position = position_local;
        data->position_global = position_global;
        data->position_real = voxel_to_real_position(position_local, chunk_position, chunk_size_b3, voxel_scale);
        data->voxel_scale = voxel_scale;
        data->chunk = chunk;
        data->normal = hit_normal;
        data->position_last = voxel_position_local_last;
        data->position_global_last = position_global_last;
        data->position_real_last = position_real_last;
        data->chunk_last = chunk_last;
        data->node_last = node_last;
    } else if (ray_hit == ray_hit_type_none) {
        data->chunk = 0;
        data->position = byte3_zero;
        data->position_global = int3_zero;
        data->normal = int3_zero;
        data->hit = float3_zero;
        data->position_real = float3_zero;
        data->position_last = byte3_zero;
        data->position_global_last = int3_zero;
        data->position_real_last = float3_zero;
        data->chunk_last = 0;
        data->node_last = NULL;
    }
    return ray_hit;
}