// Handles AABB to Voxel Chunk Collisions
// todo: support multiple realms - use a hashmap for realms, and cache their data per terrain here


/*
 * 3D Collision Detection System
 *
 *      This system handles collision detection in a 3D voxel-based environment. The main goal is to determine
 *  if an object moving within the voxel grid has collided with any solid voxels (obstacles) in the environment.
 *
 *  General Theory:
 *
 *      1. **Single Axis Collision**: Detect collisions along a single axis (x, y, or z) by checking both sides of the axis.
 *
 *      2. **Double Axis Collision**: Detect collisions along two axes simultaneously (e.g., x-z, x-y, z-y) to handle cases where movement occurs in a plane.
 *
 *      3. **Triple Axis Collision**: Detect collisions along all three axes (x, y, and z) simultaneously to handle full 3D movement and ensure no corner cases are missed.
 *
 * The process involves:
 *      - Updating the position of the object based on its movement and checking the new position against the voxel grid.
 *      - Converting real-world positions to voxel positions to determine which voxels the object occupies.
 *      - Checking the voxel grid to see if the new positions contain solid chunks3.
 *      - If a collision is detected, updating the collision status and adjusting the object's position and velocity accordingly.
 *
 * Macros are used to handle different collision scenarios efficiently by expanding the necessary function calls with appropriate parameters for single, double, and triple axis collisions.
 *
 */


// Function for 3-dimensional collision detection
void collide_with_chunk_d3(
    ecs *world,
    const ChunkLinks *chunks,
    const byte terrain_depth,
    const float scale,
    const byte *block_collisions,
    int3 voxel_position,
    const byte axis_d1,
    float position_d1,
    float position_last_d1,
    const float offset_d1,
    byte *collided_d1,
    float *distance_d1,
    const byte is_negative1,
    const byte axis_d2,
    float position_d2,
    float position_last_d2,
    const float offset_d2,
    byte *collided_d2,
    float *distance_d2,
    const byte is_negative2,
    const byte axis_d3,
    float position_d3,
    float position_last_d3,
    const float offset_d3,
    byte *collided_d3,
    float *distance_d3,
    const byte is_negative3
) {
    if (*collided_d1 || *collided_d2 || *collided_d3)  {
        return;
    }
    // Update positions with offsets
    position_last_d1 += offset_d1;
    position_last_d2 += offset_d2;
    position_last_d3 += offset_d3;
    position_d1 += offset_d1;
    position_d2 += offset_d2;
    position_d3 += offset_d3;
    const int position_vox_last_d1 = positionf_to_voxel_position1(position_last_d1, scale);
    const int position_vox_last_d2 = positionf_to_voxel_position1(position_last_d2, scale);
    const int position_vox_last_d3 = positionf_to_voxel_position1(position_last_d3, scale);
    const int position_vox_d1 = positionf_to_voxel_position1(position_d1, scale);
    const int position_vox_d2 = positionf_to_voxel_position1(position_d2, scale);
    const int position_vox_d3 = positionf_to_voxel_position1(position_d3, scale);
    if (position_vox_d1 == position_vox_last_d1 && position_vox_d2 == position_vox_last_d2 && position_vox_d3 == position_vox_last_d3)  {
        return;
    }
    const int3 chunk_dimensions = int3_single(powers_of_two[terrain_depth]);
    const byte3 chunk_dimensions_b3 = int3_to_byte3(chunk_dimensions);

    // Set dimensional variables to newer points
    int3_set_d(&voxel_position, axis_d1, position_vox_d1);
    int3_set_d(&voxel_position, axis_d2, position_vox_d2);
    int3_set_d(&voxel_position, axis_d3, position_vox_d3);
    // Convert real to voxel grid space and check voxel
    const int3 chunk_position = voxel_position_to_chunk_position(voxel_position, chunk_dimensions);
    const entity chunk = int3_hashmap_get(chunks->value, chunk_position);
    if (!zox_valid(chunk))  {
        return;
    }
    zox_geter(chunk, VoxelNode, node)
    if (!node)  {
        return;
    }
    byte3 voxel_position_local = get_local_position_byte3(voxel_position, chunk_dimensions_b3);
    if (!byte3_in_bounds(voxel_position_local, chunk_dimensions_b3)) {
        return;
    }
    zox_geter_value(chunk, NodeDepth, byte, node_depth)

    const byte voxel = get_sub_node_voxel_locked(node, &voxel_position_local, node_depth);
    if (block_collisions[voxel]) {
        // Calculate deltas
        const int delta_vox_d1 = int_abs(position_vox_d1 - position_vox_last_d1);
        const int delta_vox_d2 = int_abs(position_vox_d2 - position_vox_last_d2);
        const int delta_vox_d3 = int_abs(position_vox_d3 - position_vox_last_d3);

        if (delta_vox_d1 > delta_vox_d2 && delta_vox_d1 > delta_vox_d3) {
            *collided_d1 = 1 + is_negative1;
            //*distance_d1 = offset_d1;
            *distance_d1 = get_distance_to_voxel_grid(
                position_d1,
                *collided_d1,
                scale);
        } else if (delta_vox_d2 > delta_vox_d1 && delta_vox_d2 > delta_vox_d3) {
            *collided_d2 = 1 + is_negative2;
            //*distance_d2 = offset_d2;
            *distance_d2 = get_distance_to_voxel_grid(
                position_d2,
                *collided_d2,
                scale);
        } else {
            *collided_d3 = 1 + is_negative3;
            //*distance_d3 = offset_d3;
            *distance_d3 = get_distance_to_voxel_grid(
                position_d3,
                *collided_d3,
                scale);
        }
    }
}

// expand previous function by second dimension
void collide_with_chunk_d2(
    ecs *world,
    const ChunkLinks *chunks,
    const byte terrain_depth,
    const float terrain_scale,
    const byte *block_collisions,
    int3 voxel_position,
    const byte axis_d1,
    float position_d1,
    float position_last_d1,
    const float offset_d1,
    byte *collided_d1,
    float *distance_d1,
    const byte is_negative1,
    const byte axis_d2,
    float position_d2,
    float position_last_d2,
    const float offset_d2,
    byte *collided_d2,
    float *distance_d2,
    const byte is_negative2
) {
    if (*collided_d1 || *collided_d2)  {
        return;
    }
    position_last_d1 += offset_d1;
    position_last_d2 += offset_d2;
    position_d1 += offset_d1;
    position_d2 += offset_d2;
    const int position_vox_last_d1 = positionf_to_voxel_position1(position_last_d1, terrain_scale);
    const int position_vox_last_d2 = positionf_to_voxel_position1(position_last_d2, terrain_scale);
    const int position_vox_d1 = positionf_to_voxel_position1(position_d1, terrain_scale);
    const int position_vox_d2 = positionf_to_voxel_position1(position_d2, terrain_scale);
    if (position_vox_d1 == position_vox_last_d1 && position_vox_d2 == position_vox_last_d2) {
        return;
    }
    const int3 chunk_dimensions = (int3) { powers_of_two[terrain_depth], powers_of_two[terrain_depth], powers_of_two[terrain_depth] };
    const byte3 chunk_dimensions_b3 = int3_to_byte3(chunk_dimensions);

    int3_set_d(&voxel_position, axis_d1, position_vox_d1);
    int3_set_d(&voxel_position, axis_d2, position_vox_d2);
    const int3 chunk_position = voxel_position_to_chunk_position(voxel_position, chunk_dimensions);
    const entity chunk = int3_hashmap_get(chunks->value, chunk_position);
    if (!zox_valid(chunk)) {
        return;
    }
    zox_geter(chunk, VoxelNode, node)
    zox_geter_value(chunk, NodeDepth, byte, node_depth)
    if (!node) {
        return;
    }
    byte3 voxel_position_local = get_local_position_byte3(voxel_position, chunk_dimensions_b3);
    if (!byte3_in_bounds(voxel_position_local, chunk_dimensions_b3))  {
        return;
    }
    const byte voxel = get_sub_node_voxel_locked(node, &voxel_position_local, node_depth);
    if (block_collisions[voxel]) {
        // float_abs
        const int delta_vox_d1 = int_abs(position_vox_d1 - position_vox_last_d1);
        const int delta_vox_d2 = int_abs(position_vox_d2 - position_vox_last_d2);
        if (delta_vox_d1 > delta_vox_d2) {
            *collided_d1 = 1 + is_negative1;
            // *distance_d1 = offset_d1;
            *distance_d1 = get_distance_to_voxel_grid(
                position_d1,
                *collided_d1,
                terrain_scale);
        } else {
            *collided_d2 = 1 + is_negative2;
            // *distance_d2 = offset_d2;
            *distance_d2 = get_distance_to_voxel_grid(
                position_d2,
                *collided_d2,
                terrain_scale);
        }
        /*zox_log(" > detecting axis2 collision [%i:%i] negative [%i:%i] offsets [%f:%f] deltas [%f:%f]\n", axis_d1, axis_d2, is_negative1, is_negative2, offset_d1, offset_d2, delta_d1, delta_d2)*/
    }
}

// #define handle_collision_axisf(d, offset, is_negative)\


// Macros for handling 3-dimensional collisions
#define handle_collision_axis_d3(d1, d2, d3, offset_d1, offset_d2, offset_d3, is_negative1, is_negative2, is_negative3)\
    collide_with_chunk_d3(\
        world, \
        chunks, \
        terrain_depth, \
        terrain_scale, \
        block_collisions, \
        vpos_last, \
        zox_axis_##d1, \
        collision_point_real.d1, \
        position_last.d1, \
        offset_d1, \
        &did_collide.d1, \
        &collision_distance.d1, \
        is_negative1, \
        zox_axis_##d2, \
        collision_point_real.d2, \
        position_last.d2, \
        offset_d2, \
        &did_collide.d2, \
        &collision_distance.d2, \
        is_negative2, \
        zox_axis_##d3, \
        collision_point_real.d3, \
        position_last.d3, \
        offset_d3, \
        &did_collide.d3, \
        &collision_distance.d3, \
        is_negative3);

#define handle_collision_axis_d2(d1, d2, offset_d1, offset_d2, is_negative1, is_negative2)\
    collide_with_chunk_d2(world, \
        chunks, \
        terrain_depth, \
        terrain_scale, \
        block_collisions, \
        vpos_last, \
        zox_axis_##d1, \
        collision_point_real.d1, \
        position_last.d1, \
        offset_d1, \
        &did_collide.d1, \
        &collision_distance.d1, \
        is_negative1, \
        zox_axis_##d2, \
        collision_point_real.d2, \
        position_last.d2, \
        offset_d2, \
        &did_collide.d2, \
        &collision_distance.d2, \
        is_negative2);


void collide_with_chunk(
    ecs *world,
    const ChunkLinks *chunks,
    const byte terrain_depth,
    const float terrain_scale,
    const byte *block_collisions,
    int3 voxel_position,
    const byte axis_d,
    float position_d,
    float position_last_d,
    const float offset_d,
    byte *collided_d,
    float *distance_d,
    const byte is_negative
) {
    if (*collided_d) {
        return;
    }
    // firstt  we get our intersection line! (two points)
    position_last_d += offset_d;
    position_d += offset_d;

    const int position_vox_last_d = positionf_to_voxel_position1(position_last_d, terrain_scale);
    const int position_vox_d = positionf_to_voxel_position1(position_d, terrain_scale);

    if (position_vox_d == position_vox_last_d) {
        return;
    }

    const int3 max_chunk_size = int3_single(powers_of_two[terrain_depth]);
    // const byte3 chunk_dimensions_b3 = byte3_single(powers_of_two[terrain_depth]);
    // set dimensional variables to newer point
    int3_set_d(&voxel_position, axis_d, position_vox_d);
    // next convert real to voxel grid space and check voxel
    const int3 chunk_position = voxel_position_to_chunk_position(voxel_position, max_chunk_size);
    const entity chunk = int3_hashmap_get(chunks->value, chunk_position);
    if (!zox_valid(chunk)) {
        return;
    }
    zox_geter(chunk, VoxelNode, node);
    if (!node) {
        return;
    }

    zox_geter_value(chunk, NodeDepth, byte, chunk_depth);

    // account for node depth differences
    byte ddepth = terrain_depth - chunk_depth + 1;  // depth difference
    /*zox_log("terrain_depth: %i", terrain_depth);
    zox_log("   chunk_depth: %i", chunk_depth);
    zox_log("   ddepth: %i", ddepth);*/

    int3 voxel_position2 = int3_div1(voxel_position, (int) ddepth);
    byte3 chunk_size2 = byte3_single(powers_of_two[chunk_depth]);
    byte3 voxel_position_local = get_local_position_byte3(voxel_position2, chunk_size2);
    if (!byte3_in_bounds(voxel_position_local, chunk_size2)) {
        return;
    }

    /*byte3 voxel_position_local = get_local_position_byte3(voxel_position, chunk_dimensions_b3);
    if (!byte3_in_bounds(voxel_position_local, chunk_dimensions_b3)) {
        return;
    }*/

    const byte voxel = get_sub_node_voxel_locked(node, &voxel_position_local, chunk_depth);
    if (block_collisions[voxel]) {
        *collided_d = 1 + is_negative;

        // todo: fix for more depth
        float chunk_scale = terrain_scale / ((float) ddepth);
        *distance_d = get_distance_to_voxel_grid(
            position_d,
            *collided_d,
            chunk_scale);
        // zox_log_error("hitting chunk position [%ix%ix%i] - %f", chunk_position.x, chunk_position.y, chunk_position.z, position_d);
    }
}

#define handle_collision_axis(d, offset, is_negative)\
    collide_with_chunk(world, \
        chunks, \
        terrain_depth, \
        terrain_scale, \
        block_collisions, \
        vpos_last, \
        zox_axis_##d, \
        collision_point_real.d, \
        position_last.d, \
        offset.d, \
        &did_collide.d, \
        &collision_distance.d, \
        is_negative);


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
    byte block_collisions[voxels->length + 1];
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

        const float3 collision_point_real = position3D->value;
        const float3 position_last = lastPosition3D->value;
        float3 b = bounds3D->value;
        // const int3 collision_point_real = positionf_to_positionv(positionf, terrain_scale);
        const int3 vpos_last = positionf_to_positionv(position_last, terrain_scale);
        // normalize xz for now, until rotations
        // if (b.x > b.z) b.z = b.x;
        // else b.x = b.z;
        const float3 bounds_left = float3_scale(b, -1);
        const float3 bounds_right = b;

        // new detection
        byte3 did_collide = byte3_zero;
        float3 collision_distance;

        /* single axis collision, two sides per axis*/
        handle_collision_axis(x, bounds_left, 1)
        handle_collision_axis(x, bounds_right, 0)
        handle_collision_axis(y, bounds_left, 1)
        handle_collision_axis(y, bounds_right, 0)
        handle_collision_axis(z, bounds_left, 1)
        handle_collision_axis(z, bounds_right, 0)

        // double axis collision, fours sides per two axis
        handle_collision_axis_d2(x, z, bounds_left.x, bounds_left.z, 1, 1)
        handle_collision_axis_d2(x, z, bounds_right.x, bounds_left.z, 0, 1)
        handle_collision_axis_d2(x, z, bounds_left.x, bounds_right.z, 1, 0)
        handle_collision_axis_d2(x, z, bounds_right.x, bounds_right.z, 0, 0)
        handle_collision_axis_d2(x, y, bounds_left.x, bounds_left.y, 1, 1)
        handle_collision_axis_d2(x, y, bounds_right.x, bounds_left.y, 0, 1)
        handle_collision_axis_d2(x, y, bounds_left.x, bounds_right.y, 1, 0)
        handle_collision_axis_d2(x, y, bounds_right.x, bounds_right.y, 0, 0)
        handle_collision_axis_d2(y, z, bounds_left.y, bounds_left.z, 1, 1)
        handle_collision_axis_d2(y, z, bounds_right.y, bounds_left.z, 0, 1)
        handle_collision_axis_d2(y, z, bounds_left.y, bounds_right.z, 1, 0)
        handle_collision_axis_d2(y, z, bounds_right.y, bounds_right.z, 0, 0)

        // three axis collision
        handle_collision_axis_d3(x, y, z, bounds_left.x, bounds_left.y, bounds_left.z, 1, 1, 1);
        handle_collision_axis_d3(x, y, z, bounds_right.x, bounds_left.y, bounds_left.z, 0, 1, 1);
        handle_collision_axis_d3(x, y, z, bounds_left.x, bounds_right.y, bounds_left.z, 1, 0, 1);
        handle_collision_axis_d3(x, y, z, bounds_right.x, bounds_right.y, bounds_left.z, 0, 0, 1);
        handle_collision_axis_d3(x, y, z, bounds_left.x, bounds_left.y, bounds_right.z, 1, 1, 0);
        handle_collision_axis_d3(x, y, z, bounds_right.x, bounds_left.y, bounds_right.z, 0, 1, 0);
        handle_collision_axis_d3(x, y, z, bounds_left.x, bounds_right.y, bounds_right.z, 1, 0, 0);
        handle_collision_axis_d3(x, y, z, bounds_right.x, bounds_right.y, bounds_right.z, 0, 0, 0);

        // pack the collision
        if (did_collide.x || did_collide.y || did_collide.z) {
            collisionDistance->value = collision_distance;
            collision->value = ( did_collide.x & 0x3) << 0 | (did_collide.y & 0x3) << 2  | (did_collide.z & 0x3) << 4;
        }

    }
} zoxd_system(CollisionDetectSystem)






/*#ifdef zoxel_debug_basic_collision3D_system
        if (voxelPosition->value.x >= default_chunk_length || voxelPosition->value.y >= default_chunk_length || voxelPosition->value.z >= default_chunk_length) {
            zox_log(" !!! voxel position set out of bounds !!!\n");
            zox_log(" !> chunk_position [%ix%ix%i]\n", chunk_position.x, chunk_position.y, chunk_position.z);
            zox_log("     !+ global voxel position [%ix%ix%i]\n", global_voxel_position.x, global_voxel_position.y, global_voxel_position.z);
            zox_log("     !+ local voxel position [%ix%ix%i]\n", new_position.x, new_position.y, new_position.z);
            zox_log("     !+ real position [%fx%fx%f]\n", collision_point_real.x, collision_point_real.y, collision_point_real.z);
        } else {
            // zox_log(" > chunk_position [%ix%ix%i]\n", chunkPosition->value.x, chunkPosition->value.y, chunkPosition->value.z);
            zox_log("     + voxel position updated [%ix%ix%i]\n", new_position.x, new_position.y, new_position.z);
            zox_log("     + global voxel position [%ix%ix%i]\n", global_voxel_position.x, global_voxel_position.y, global_voxel_position.z);
            zox_log("     + real position was [%fx%fx%f]\n", collision_point_real.x, collision_point_real.y, collision_point_real.z);
        }
#endif*/




/*#ifdef zoxel_debug_basic_collision3D_system
        if (did_collide_y && voxelPosition->value.x >= default_chunk_length || voxelPosition->value.y >= default_chunk_length || voxelPosition->value.z >= default_chunk_length) {
            zox_log(" !!! voxel position set out of bounds\n");
            zox_log(" ! > chunk_position [%ix%ix%i]\n", chunkPosition->value.x, chunkPosition->value.y, chunkPosition->value.z);
            zox_log("     ! + voxel position updated [%ix%ix%i]\n", new_position.x, new_position.y, new_position.z);
            zox_log("     ! + real position was [%fx%fx%f]\n", collision_point_real.x, collision_point_real.y, collision_point_real.z);
        }
#endif*/