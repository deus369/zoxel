byte is_do_all_collision_points = 0;
const byte collision_check_types = 1;
const float collision_check_delta = 0.25f;
#define collision_fudge 0

static inline float3 bias_sample_by_movement(float3 sample, const byte3 movement_axis) {
    if (movement_axis.x == 1) sample.x += collision_fudge;
    else if (movement_axis.x == 2) sample.x -= collision_fudge;
    if (movement_axis.y == 1) sample.y += collision_fudge;
    else if (movement_axis.y == 2) sample.y -= collision_fudge;
    if (movement_axis.z == 1) sample.z += collision_fudge;
    else if (movement_axis.z == 2) sample.z -= collision_fudge;
    return sample;
}


byte check_collision_point(
    ecs *world,
    const ChunkLinks *chunks,
    const byte terrain_depth,
    const float terrain_scale,
    const byte *block_collisions,
    const float3 positionf
) {
    // voxel position from real
    const int3 positionv = positionf_to_positionv(positionf, terrain_scale);

    // get chunk from position
    const int3 positionc = real_position_to_chunk_position(
        positionf,
        powers_of_two[terrain_depth],
        terrain_scale);
    const entity chunk = int3_hashmap_get(chunks->value, positionc);
    if (!zox_valid(chunk)) {
        return 0;
    }
    zox_geter(chunk, VoxelNode, node);
    if (!node) {
        return 0;
    }

    // check local position
    const byte3 chunk_size = byte3_single(powers_of_two[terrain_depth]);
    byte3 positionl = get_local_position_byte3(
        positionv,
        chunk_size
    );
    if (!byte3_in_bounds(positionl, chunk_size)) {
        return 0;
    }

    zox_geter_value(chunk, NodeDepth, byte, chunk_depth);
    const byte voxel = get_sub_node_voxel_locked(
        node,
        &positionl,
        chunk_depth);

    return (block_collisions[voxel]);
}

void collide_with_chunkf(
    ecs *world,
    const ChunkLinks *chunks,
    const byte terrain_depth,
    const float terrain_scale,
    const byte *block_collisions,
    float3 pointf_new,
    float3 pointf_last,
    const float3 offset,
    const byte3 movement_axis,
    byte3 *did_collide,
    float3 *closestd,
    byte check_type // single, double, tripple
) {

    byte3 axis_check = movement_axis;
    byte3 old_did_collide = *did_collide;
    float3 sample;

    if (check_type == 0) {

        sample = (float3) { pointf_last.x, pointf_new.y, pointf_last.z };
        sample = bias_sample_by_movement(sample, movement_axis);
        did_collide->y |= axis_check.y &&
            check_collision_point(
                world,
                chunks,
                terrain_depth,
                terrain_scale,
                block_collisions,
                sample
            );

        sample = (float3) { pointf_new.x, pointf_last.y, pointf_last.z };
        sample = bias_sample_by_movement(sample, movement_axis);
        did_collide->x |= axis_check.x &&
            check_collision_point(
                world,
                chunks,
                terrain_depth,
                terrain_scale,
                block_collisions,
                sample
            );

        sample = (float3) { pointf_last.x, pointf_last.y, pointf_new.z };
        sample = bias_sample_by_movement(sample, movement_axis);
        did_collide->z |= axis_check.z &&
            check_collision_point(
                world,
                chunks,
                terrain_depth,
                terrain_scale,
                block_collisions,
                sample
            );
    }

    else if (check_type == 1) {
        if (!did_collide->y && !did_collide->z && axis_check.y && axis_check.z) {
            sample = (float3) { pointf_last.x, pointf_new.y, pointf_new.z };
            sample = bias_sample_by_movement(sample, movement_axis);
            byte did_collide_yz = check_collision_point(
                world,
                chunks,
                terrain_depth,
                terrain_scale,
                block_collisions,
                sample);
            if (did_collide_yz) {
                did_collide->y = 1;
                did_collide->z = 1;
            }
        }

        if (!did_collide->x && !did_collide->y && axis_check.x && axis_check.y) {
            sample = (float3) { pointf_new.x, pointf_new.y, pointf_last.z };
            sample = bias_sample_by_movement(sample, movement_axis);
            byte did_collide_xy = check_collision_point(
                world,
                chunks,
                terrain_depth,
                terrain_scale,
                block_collisions,
                sample);
            if (did_collide_xy) {
                did_collide->x = 1;
                did_collide->y = 1;
            }
        }

        if (!did_collide->x && !did_collide->z && axis_check.x && axis_check.z) {
            sample = (float3) { pointf_new.x, pointf_last.y, pointf_new.z };
            sample = bias_sample_by_movement(sample, movement_axis);
            byte did_collide_xz = check_collision_point(
                world,
                chunks,
                terrain_depth,
                terrain_scale,
                block_collisions,
                sample);
            if (did_collide_xz) {
                did_collide->x = 1;
                did_collide->z = 1;
            }
        }
    }

    // tripple axis check
    else if (check_type == 2) {
        if (!did_collide->x && !did_collide->y && !did_collide->z &&
            axis_check.x && axis_check.y && axis_check.z) {
            sample = pointf_new;
            sample = bias_sample_by_movement(sample, movement_axis);
            byte did_collide_xyz = check_collision_point(
                world,
                chunks,
                terrain_depth,
                terrain_scale,
                block_collisions,
                sample);
            if (did_collide_xyz) {
                did_collide->x = 1;
                did_collide->y = 1;
                did_collide->z = 1;
            }
        }
    }

    // logs penetration distance ish
    // issue is we are storing the offset, rather than penetration distance

    if (old_did_collide.y != did_collide->y && did_collide->y && axis_check.y) {
        float penetration = get_distance_to_voxel_grid(pointf_new.y, movement_axis.y, terrain_scale);
        if (penetration < closestd->y) {
            closestd->y = penetration;
        }
    }

    if (old_did_collide.x != did_collide->x && did_collide->x && axis_check.x) {
        float penetration = get_distance_to_voxel_grid(pointf_new.x, movement_axis.x, terrain_scale);
        if (penetration < closestd->x) {
            closestd->x = penetration;
        }
    }

    if (old_did_collide.z != did_collide->z && did_collide->z && axis_check.z) {
        float penetration = get_distance_to_voxel_grid(pointf_new.z, movement_axis.z, terrain_scale);
        if (penetration < closestd->z) {
            closestd->z = penetration;
        }
    }
}

void CollisionDetectSystem(iter *it) {
    zox_sys_world();
    zox_sys_begin();
    zox_sys_in(VoxLink);
    zox_sys_in(Bounds3D);
    zox_sys_in(Position3D);
    zox_sys_in(LastPosition3D);
    zox_sys_out(Collision);
    zox_sys_out(CollisionDistance);
    // find realm first
    const VoxelLinks *voxels = get_first_terrain_voxels(world, VoxLink_, it->count);
    if (!voxels) {
        return;
    }
    byte block_collisions[voxels->length + 1]; // 255];
    get_block_collisions(world, voxels, block_collisions);

    // now do collisions
    for (int i = 0; i < it->count; i++) {
        zox_sys_i(VoxLink, voxLink);
        zox_sys_i(Bounds3D, bounds3D);
        zox_sys_i(Position3D, position3D);
        zox_sys_i(LastPosition3D, lastPosition3D);
        zox_sys_o(Collision, collision);
        zox_sys_o(CollisionDistance, collisionDistance);
        if (!zox_valid(voxLink->value)) {
            continue; // these shouldn't be here
        }
        zox_geter(voxLink->value, ChunkLinks, chunks);
        zox_geter_value(voxLink->value, NodeDepth, byte, terrain_depth);
        zox_geter_value(voxLink->value, VoxScale, float, terrain_scale);
        if (!chunks || collision->value) {
            continue;
        }

        const float3 pointf_new = position3D->value;
        const float3 pointf_last = lastPosition3D->value;
        float3 b = bounds3D->value;
        // normalize xz for now, until rotations
        // if (b.x > b.z) b.z = b.x;
        // else b.x = b.z;
        const float3 bounds_left = float3_scale(b, -1);
        const float3 bounds_right = b;


        // 0 None, 1 Right, 2 Left
        byte3 movement_axis = (byte3) {
            pointf_last.x == pointf_new.x ? 0 : pointf_new.x > pointf_last.x ? 1 : 2,
            pointf_last.y == pointf_new.y ? 0 : pointf_new.y > pointf_last.y ? 1 : 2,
            pointf_last.z == pointf_new.z ? 0 : pointf_new.z > pointf_last.z ? 1 : 2
        };

        // new detection
        float3 offset;
        byte3 did_collide = byte3_zero;
        float3 closestd = { FLT_MAX, FLT_MAX, FLT_MAX };

        for (byte check_type = 0; check_type < collision_check_types; check_type++) {
        // for (sbyte check_type = collision_check_types - 1; check_type >= 0; check_type--) {
            if (is_do_all_collision_points) {
                const float3 delta = (float3) {
                    (bounds_right.x - bounds_left.x) / collision_check_delta,
                    (bounds_right.y - bounds_left.y) / collision_check_delta,
                    (bounds_right.z - bounds_left.z) / collision_check_delta
                };
                for (float x = bounds_left.x; x <= bounds_right.x; x += delta.x) {
                    for (float y = bounds_left.y; y <= bounds_right.y; y += delta.y) {
                        for (float z = bounds_left.z; z <= bounds_right.z; z += delta.z) {
                            if (x == 0 || y == 0 || z == 0) {
                                continue;
                            }
                            offset = (float3) { x, y, z };
                            collide_with_chunkf(
                                world,
                                chunks,
                                terrain_depth,
                                terrain_scale,
                                block_collisions,
                                float3_add(pointf_new, offset),
                                float3_add(pointf_last, offset),
                                offset,
                                movement_axis,
                                &did_collide,
                                &closestd,
                                check_type);
                        }
                    }
                }
            } else {
                float3 offsets[] = {
                    (float3) { 0, bounds_left.y, 0 },
                    (float3) { 0, bounds_right.y, 0 },
                    (float3) { bounds_left.x, 0, 0 },
                    (float3) { bounds_right.x, 0, 0 },
                    (float3) { 0, 0, bounds_left.z },
                    (float3) { 0, 0, bounds_right.z },
                };
                for (byte j = 0; j < 6; j++) {
                    offset = offsets[j];
                    collide_with_chunkf(
                        world,
                        chunks,
                        terrain_depth,
                        terrain_scale,
                        block_collisions,
                        float3_add(pointf_new, offset),
                        float3_add(pointf_last, offset),
                        offset,
                        movement_axis,
                        &did_collide,
                        &closestd,
                        check_type);
                }
            }
        }

        // add info about direction
        if (did_collide.x) did_collide.x = movement_axis.x;
        if (did_collide.y) did_collide.y = movement_axis.y;
        if (did_collide.z) did_collide.z = movement_axis.z;

        // pack the collision
        if (did_collide.x || did_collide.y || did_collide.z) {
            collisionDistance->value = closestd;
            collision->value = ( did_collide.x & 0x3) << 0 | (did_collide.y & 0x3) << 2  | (did_collide.z & 0x3) << 4;
        }

    }
} zoxd_system(CollisionDetectSystem)