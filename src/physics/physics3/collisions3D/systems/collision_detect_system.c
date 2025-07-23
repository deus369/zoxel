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
void collide_with_chunk_d3(ecs_world_t *world,
    const ChunkLinks *chunk_links,
    const byte max_depth,
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
    const byte is_negative3)
{
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
    const int position_vox_last_d1 = real_position_to_voxel_position_dim(position_last_d1, max_depth);
    const int position_vox_last_d2 = real_position_to_voxel_position_dim(position_last_d2, max_depth);
    const int position_vox_last_d3 = real_position_to_voxel_position_dim(position_last_d3, max_depth);
    const int position_vox_d1 = real_position_to_voxel_position_dim(position_d1, max_depth);
    const int position_vox_d2 = real_position_to_voxel_position_dim(position_d2, max_depth);
    const int position_vox_d3 = real_position_to_voxel_position_dim(position_d3, max_depth);
    if (position_vox_d1 == position_vox_last_d1 && position_vox_d2 == position_vox_last_d2 && position_vox_d3 == position_vox_last_d3)  {
        return;
    }
    const int3 chunk_dimensions = (int3) { powers_of_two[max_depth], powers_of_two[max_depth], powers_of_two[max_depth] };
    const byte3 chunk_dimensions_b3 = int3_to_byte3(chunk_dimensions);

    // Set dimensional variables to newer points
    int3_set_d(&voxel_position, axis_d1, position_vox_d1);
    int3_set_d(&voxel_position, axis_d2, position_vox_d2);
    int3_set_d(&voxel_position, axis_d3, position_vox_d3);
    // Convert real to voxel grid space and check voxel
    const int3 chunk_position = voxel_position_to_chunk_position(voxel_position, chunk_dimensions);
    const ecs_entity_t chunk = int3_hashmap_get(chunk_links->value, chunk_position);
    if (!zox_valid(chunk))  {
        return;
    }
    zox_geter(chunk, VoxelNode, node)
    if (!node)  {
        return;
    }
    byte3 voxel_position_local = get_local_position_byte3(voxel_position, chunk_position, chunk_dimensions_b3);
    if (!byte3_in_bounds(voxel_position_local, chunk_dimensions_b3)) {
        return;
    }
    zox_geter_value(chunk, NodeDepth, byte, node_depth)

    const byte voxel = get_sub_node_voxel(node, &voxel_position_local, node_depth);
    if (block_collisions[voxel]) {
        // Calculate deltas
        const int delta_vox_d1 = int_abs(position_vox_d1 - position_vox_last_d1);
        const int delta_vox_d2 = int_abs(position_vox_d2 - position_vox_last_d2);
        const int delta_vox_d3 = int_abs(position_vox_d3 - position_vox_last_d3);

        if (delta_vox_d1 > delta_vox_d2 && delta_vox_d1 > delta_vox_d3) {
            *collided_d1 = 1 + is_negative1;
            *distance_d1 = offset_d1;
        } else if (delta_vox_d2 > delta_vox_d1 && delta_vox_d2 > delta_vox_d3) {
            *collided_d2 = 1 + is_negative2;
            *distance_d2 = offset_d2;
        } else {
            *collided_d3 = 1 + is_negative3;
            *distance_d3 = offset_d3;
        }
    }
}

// expand previous function by second dimension
void collide_with_chunk_d2(ecs_world_t *world,
    const ChunkLinks *chunk_links,
    const byte max_depth,
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
    const byte is_negative2)
{
    if (*collided_d1 || *collided_d2)  {
        return;
    }
    position_last_d1 += offset_d1;
    position_last_d2 += offset_d2;
    position_d1 += offset_d1;
    position_d2 += offset_d2;
    const int position_vox_last_d1 = real_position_to_voxel_position_dim(position_last_d1, max_depth);
    const int position_vox_last_d2 = real_position_to_voxel_position_dim(position_last_d2, max_depth);
    const int position_vox_d1 = real_position_to_voxel_position_dim(position_d1, max_depth);
    const int position_vox_d2 = real_position_to_voxel_position_dim(position_d2, max_depth);
    if (position_vox_d1 == position_vox_last_d1 && position_vox_d2 == position_vox_last_d2) {
        return;
    }
    const int3 chunk_dimensions = (int3) { powers_of_two[max_depth], powers_of_two[max_depth], powers_of_two[max_depth] };
    const byte3 chunk_dimensions_b3 = int3_to_byte3(chunk_dimensions);

    int3_set_d(&voxel_position, axis_d1, position_vox_d1);
    int3_set_d(&voxel_position, axis_d2, position_vox_d2);
    const int3 chunk_position = voxel_position_to_chunk_position(voxel_position, chunk_dimensions);
    const ecs_entity_t chunk = int3_hashmap_get(chunk_links->value, chunk_position);
    if (!zox_valid(chunk)) {
        return;
    }
    zox_geter(chunk, VoxelNode, chunk_octree)
    zox_geter_value(chunk, NodeDepth, byte, node_depth)
    if (!chunk_octree) {
        return;
    }
    byte3 voxel_position_local = get_local_position_byte3(voxel_position, chunk_position, chunk_dimensions_b3);
    if (!byte3_in_bounds(voxel_position_local, chunk_dimensions_b3))  {
        return;
    }
    const byte voxel = get_sub_node_voxel(chunk_octree, &voxel_position_local, node_depth);
    if (block_collisions[voxel]) {
        // float_abs
        const int delta_vox_d1 = int_abs(position_vox_d1 - position_vox_last_d1);
        const int delta_vox_d2 = int_abs(position_vox_d2 - position_vox_last_d2);
        if (delta_vox_d1 > delta_vox_d2) {
            *collided_d1 = 1 + is_negative1;
            *distance_d1 = offset_d1;
        } else {
            *collided_d2 = 1 + is_negative2;
            *distance_d2 = offset_d2;
        }
        /*zox_log(" > detecting axis2 collision [%i:%i] negative [%i:%i] offsets [%f:%f] deltas [%f:%f]\n", axis_d1, axis_d2, is_negative1, is_negative2, offset_d1, offset_d2, delta_d1, delta_d2)*/
    }
}

void collide_with_chunk(ecs_world_t *world,
    const ChunkLinks *chunk_links,
    const byte max_depth,
    const byte *block_collisions,
    int3 voxel_position,
    const byte axis_d,
    float position_d,
    float position_last_d,
    const float offset_d,
    byte *collided_d,
    float *distance_d,
    const byte is_negative)
{
    if (*collided_d) {
        return;
    }
    // firstt  we get our intersection line! (two points)
    position_last_d += offset_d;
    position_d += offset_d;
    const int position_vox_last_d = real_position_to_voxel_position_dim(position_last_d, max_depth);
    const int position_vox_d = real_position_to_voxel_position_dim(position_d, max_depth);
    if (position_vox_d == position_vox_last_d) {
        return;
    }
    const int3 chunk_dimensions = (int3) { powers_of_two[max_depth], powers_of_two[max_depth], powers_of_two[max_depth] };
    const byte3 chunk_dimensions_b3 = int3_to_byte3(chunk_dimensions);

    // set dimensional variables to newer point
    int3_set_d(&voxel_position, axis_d, position_vox_d);
    // next convert real to voxel grid space and check voxel
    const int3 chunk_position = voxel_position_to_chunk_position(voxel_position, chunk_dimensions);
    const ecs_entity_t chunk = int3_hashmap_get(chunk_links->value, chunk_position);
    if (!zox_valid(chunk)) {
        return;
    }
    zox_geter(chunk, VoxelNode, chunk_octree)
    zox_geter_value(chunk, NodeDepth, byte, node_depth)
    if (!chunk_octree) {
        return;
    }
    byte3 voxel_position_local = get_local_position_byte3(voxel_position, chunk_position, chunk_dimensions_b3);
    if (!byte3_in_bounds(voxel_position_local, chunk_dimensions_b3)) {
        return;
    }
    const byte voxel = get_sub_node_voxel(chunk_octree, &voxel_position_local, node_depth);
    if (block_collisions[voxel]) {
        *collided_d = 1 + is_negative;
        *distance_d = offset_d;
    }
}

// Macros for handling 3-dimensional collisions
#define handle_collision_axis_d3(d1, d2, d3, offset_d1, offset_d2, offset_d3, is_negative1, is_negative2, is_negative3)\
collide_with_chunk_d3(world, chunkLinks, max_depth, block_collisions, real_position_to_voxel_position(position_last, max_depth), zox_axis_##d1, collision_point_real.d1, position_last.d1, offset_d1, &did_collide_##d1, &collision_distance.d1, is_negative1, zox_axis_##d2, collision_point_real.d2, position_last.d2, offset_d2, &did_collide_##d2, &collision_distance.d2, is_negative2, zox_axis_##d3, collision_point_real.d3, position_last.d3, offset_d3, &did_collide_##d3, &collision_distance.d3, is_negative3);

#define handle_collision_axis_d2(d1, d2, offset_d1, offset_d2, is_negative1, is_negative2)\
    collide_with_chunk_d2(world, chunkLinks, max_depth, block_collisions, real_position_to_voxel_position(position_last, max_depth), zox_axis_##d1, collision_point_real.d1, position_last.d1, offset_d1, &did_collide_##d1, &collision_distance.d1, is_negative1, zox_axis_##d2, collision_point_real.d2, position_last.d2, offset_d2, &did_collide_##d2, &collision_distance.d2, is_negative2);

#define handle_collision_axis(d, offset, is_negative)\
    collide_with_chunk(world, chunkLinks, max_depth, block_collisions, real_position_to_voxel_position(position_last, max_depth), zox_axis_##d, collision_point_real.d,  position_last.d, offset.d, &did_collide_##d, &collision_distance.d, is_negative);

#define detect_voxel_collisions()\
    const float3 offset_left = float3_scale(bounds3D->value, -1);\
    const float3 offset_right = bounds3D->value;\
    \
    /* single axis collision, two sides per axis*/\
    handle_collision_axis(x, offset_left, 1)\
    handle_collision_axis(x, offset_right, 0)\
    handle_collision_axis(y, offset_left, 1)\
    handle_collision_axis(y, offset_right, 0)\
    handle_collision_axis(z, offset_left, 1)\
    handle_collision_axis(z, offset_right, 0)\
    \
    /* double axis collision, fours sides per two axis*/\
    handle_collision_axis_d2(x, z, offset_left.x, offset_left.z, 1, 1)\
    handle_collision_axis_d2(x, z, offset_right.x, offset_left.z, 0, 1)\
    handle_collision_axis_d2(x, z, offset_left.x, offset_right.z, 1, 0)\
    handle_collision_axis_d2(x, z, offset_right.x, offset_right.z, 0, 0)\
    handle_collision_axis_d2(x, y, offset_left.x, offset_left.y, 1, 1)\
    handle_collision_axis_d2(x, y, offset_right.x, offset_left.y, 0, 1)\
    handle_collision_axis_d2(x, y, offset_left.x, offset_right.y, 1, 0)\
    handle_collision_axis_d2(x, y, offset_right.x, offset_right.y, 0, 0)\
    handle_collision_axis_d2(y, z, offset_left.y, offset_left.z, 1, 1)\
    handle_collision_axis_d2(y, z, offset_right.y, offset_left.z, 0, 1)\
    handle_collision_axis_d2(y, z, offset_left.y, offset_right.z, 1, 0)\
    handle_collision_axis_d2(y, z, offset_right.y, offset_right.z, 0, 0)\
    \
    /* three axis collision*/\
    handle_collision_axis_d3(x, y, z, offset_left.x, offset_left.y, offset_left.z, 1, 1, 1)\
    handle_collision_axis_d3(x, y, z, offset_right.x, offset_left.y, offset_left.z, 0, 1, 1)\
    handle_collision_axis_d3(x, y, z, offset_left.x, offset_right.y, offset_left.z, 1, 0, 1)\
    handle_collision_axis_d3(x, y, z, offset_right.x, offset_right.y, offset_left.z, 0, 0, 1)\
    handle_collision_axis_d3(x, y, z, offset_left.x, offset_left.y, offset_right.z, 1, 1, 0)\
    handle_collision_axis_d3(x, y, z, offset_right.x, offset_left.y, offset_right.z, 0, 1, 0)\
    handle_collision_axis_d3(x, y, z, offset_left.x, offset_right.y, offset_right.z, 1, 0, 0)\
    handle_collision_axis_d3(x, y, z, offset_right.x, offset_right.y, offset_right.z, 0, 0, 0)


void CollisionDetectSystem(ecs_iter_t *it) {
    const byte max_depth = terrain_depth;   // todo: use chunk max depths here
    zox_sys_world()
    zox_sys_begin()
    zox_sys_in(VoxLink)
    zox_sys_in(Bounds3D)
    zox_sys_in(Position3D)
    // zox_sys_in(Velocity3D)
    zox_sys_in(LastPosition3D)
    zox_sys_out(Collision)
    zox_sys_out(CollisionDistance)
    // find realm first
    const VoxelLinks *voxels = get_first_terrain_voxels(world, VoxLink_, it->count);
    if (!voxels) {
        return;
    }
    byte block_collisions[voxels->length + 1]; // 255];
    get_block_collisions(world, voxels, block_collisions);

    // now do collisions
    for (int i = 0; i < it->count; i++) {
        zox_sys_i(VoxLink, voxLink)
        zox_sys_i(Bounds3D, bounds3D)
        zox_sys_i(Position3D, position3D)
        // zox_sys_i(Velocity3D, velocity3D)
        zox_sys_i(LastPosition3D, lastPosition3D)
        zox_sys_o(Collision, collision)
        zox_sys_o(CollisionDistance, collisionDistance)
#ifdef zoxel_debug_basic_collision3D_system
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
#endif
        if (!zox_valid(voxLink->value)) {
            continue; // these shouldn't be here
        }
        zox_geter(voxLink->value, ChunkLinks, chunkLinks)
        if (!chunkLinks) {
            continue;
        }
        if (collision->value) {
            continue;
        }
        const float3 position_last = lastPosition3D->value;
        // const float3 position_new = position3D->value;
        float3 collision_point_real = position3D->value;
        float3 collision_distance = float3_zero;
        byte did_collide_x = 0;
        byte did_collide_y = 0;
        byte did_collide_z = 0;
        detect_voxel_collisions()

        // pack the collision
        if (did_collide_x || did_collide_y || did_collide_z) {
            collisionDistance->value = collision_distance;
            collision->value = (did_collide_x & 0x3) << 0 | (did_collide_y & 0x3) << 2  | (did_collide_z & 0x3) << 4;
        }

#ifdef zoxel_debug_basic_collision3D_system
        if (did_collide_y && voxelPosition->value.x >= default_chunk_length || voxelPosition->value.y >= default_chunk_length || voxelPosition->value.z >= default_chunk_length) {
            zox_log(" !!! voxel position set out of bounds\n");
            zox_log(" ! > chunk_position [%ix%ix%i]\n", chunkPosition->value.x, chunkPosition->value.y, chunkPosition->value.z);
            zox_log("     ! + voxel position updated [%ix%ix%i]\n", new_position.x, new_position.y, new_position.z);
            zox_log("     ! + real position was [%fx%fx%f]\n", collision_point_real.x, collision_point_real.y, collision_point_real.z);
        }
#endif

    }
} zox_declare_system(CollisionDetectSystem)