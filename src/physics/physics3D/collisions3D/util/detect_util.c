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
 *      - Checking the voxel grid to see if the new positions contain solid voxels.
 *      - If a collision is detected, updating the collision status and adjusting the object's position and velocity accordingly.
 *
 * Macros are used to handle different collision scenarios efficiently by expanding the necessary function calls with appropriate parameters for single, double, and triple axis collisions.
 *
 */

// Function for 3-dimensional collision detection
void collide_with_chunk_d3(const ChunkLinks *chunk_links, const byte *block_collisions, int3 voxel_position,
    const byte axis_d1, float position_d1, float position_last_d1, const float offset_d1, byte *collided_d1, float *distance_d1, const byte is_negative1,
    const byte axis_d2, float position_d2, float position_last_d2, const float offset_d2, byte *collided_d2, float *distance_d2, const byte is_negative2,
    const byte axis_d3, float position_d3, float position_last_d3, const float offset_d3, byte *collided_d3, float *distance_d3, const byte is_negative3) {
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
    const int position_vox_last_d1 = real_position_to_voxel_position_dim(position_last_d1);
    const int position_vox_last_d2 = real_position_to_voxel_position_dim(position_last_d2);
    const int position_vox_last_d3 = real_position_to_voxel_position_dim(position_last_d3);
    const int position_vox_d1 = real_position_to_voxel_position_dim(position_d1);
    const int position_vox_d2 = real_position_to_voxel_position_dim(position_d2);
    const int position_vox_d3 = real_position_to_voxel_position_dim(position_d3);
    if (position_vox_d1 == position_vox_last_d1 && position_vox_d2 == position_vox_last_d2 && position_vox_d3 == position_vox_last_d3)  {
        return;
    }
    // Set dimensional variables to newer points
    int3_set_d(&voxel_position, axis_d1, position_vox_d1);
    int3_set_d(&voxel_position, axis_d2, position_vox_d2);
    int3_set_d(&voxel_position, axis_d3, position_vox_d3);
    // Convert real to voxel grid space and check voxel
    const int3 chunk_position = voxel_position_to_chunk_position(voxel_position, default_chunk_size);
    const ecs_entity_t chunk = int3_hashmap_get(chunk_links->value, chunk_position);
    if (!zox_valid(chunk))  {
        return;
    }
    const ChunkOctree *chunk_octree = zox_get(chunk, ChunkOctree);
    if (!chunk_octree)  {
        return;
    }
    byte3 voxel_position_local = get_local_position_byte3(voxel_position, chunk_position, default_chunk_size_byte3);
    if (!byte3_in_bounds(voxel_position_local, default_chunk_size_byte3)) return;

    const byte voxel = get_octree_voxel(chunk_octree, &voxel_position_local, max_octree_depth);
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

// Macros for handling 3-dimensional collisions
#define handle_collision_axis_d3(d1, d2, d3, offset_d1, offset_d2, offset_d3, is_negative1, is_negative2, is_negative3) \
    collide_with_chunk_d3(chunkLinks, block_collisions, real_position_to_voxel_position(position_last), \
    zox_axis##_##d1, collision_point_real.d1, position_last.d1, offset_d1, &did_collide##_##d1, &collision_offset.d1, is_negative1, \
    zox_axis##_##d2, collision_point_real.d2, position_last.d2, offset_d2, &did_collide##_##d2, &collision_offset.d2, is_negative2, \
    zox_axis##_##d3, collision_point_real.d3, position_last.d3, offset_d3, &did_collide##_##d3, &collision_offset.d3, is_negative3);


// expand previous function by second dimension
void collide_with_chunk_d2(const ChunkLinks *chunk_links, const byte *block_collisions, int3 voxel_position, const byte axis_d1, float position_d1, float position_last_d1, const float offset_d1, byte *collided_d1, float *distance_d1, const byte is_negative1, const byte axis_d2, float position_d2, float position_last_d2, const float offset_d2, byte *collided_d2, float *distance_d2, const byte is_negative2) {
    if (*collided_d1 || *collided_d2)  {
        return;
    }
    position_last_d1 += offset_d1;
    position_last_d2 += offset_d2;
    position_d1 += offset_d1;
    position_d2 += offset_d2;
    const int position_vox_last_d1 = real_position_to_voxel_position_dim(position_last_d1);
    const int position_vox_last_d2 = real_position_to_voxel_position_dim(position_last_d2);
    const int position_vox_d1 = real_position_to_voxel_position_dim(position_d1);
    const int position_vox_d2 = real_position_to_voxel_position_dim(position_d2);
    if (position_vox_d1 == position_vox_last_d1 && position_vox_d2 == position_vox_last_d2) {
        return;
    }
    int3_set_d(&voxel_position, axis_d1, position_vox_d1);
    int3_set_d(&voxel_position, axis_d2, position_vox_d2);
    const int3 chunk_position = voxel_position_to_chunk_position(voxel_position, default_chunk_size);
    const ecs_entity_t chunk = int3_hashmap_get(chunk_links->value, chunk_position);
    if (!zox_valid(chunk)) {
        return;
    }
    const ChunkOctree *chunk_octree = zox_get(chunk, ChunkOctree)
    if (!chunk_octree) {
        return;
    }
    byte3 voxel_position_local = get_local_position_byte3(voxel_position, chunk_position, default_chunk_size_byte3);
    if (!byte3_in_bounds(voxel_position_local, default_chunk_size_byte3))  {
        return;
    }
    const byte voxel = get_octree_voxel(chunk_octree, &voxel_position_local, max_octree_depth);
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

void collide_with_chunk(const ChunkLinks *chunk_links, const byte *block_collisions, int3 voxel_position, const byte axis_d, float position_d, float position_last_d, const float offset_d, byte *collided_d, float *distance_d, const byte is_negative) {
    if (*collided_d) {
        return;
    }
    // firstt  we get our intersection line! (two points)
    position_last_d += offset_d;
    position_d += offset_d;
    const int position_vox_last_d = real_position_to_voxel_position_dim(position_last_d);
    const int position_vox_d = real_position_to_voxel_position_dim(position_d);
    if (position_vox_d == position_vox_last_d) {
        return;
    }
    // set dimensional variables to newer point
    int3_set_d(&voxel_position, axis_d, position_vox_d);
    // next convert real to voxel grid space and check voxel
    const int3 chunk_position = voxel_position_to_chunk_position(voxel_position, default_chunk_size);
    const ecs_entity_t chunk = int3_hashmap_get(chunk_links->value, chunk_position);
    if (!zox_valid(chunk)) {
        return;
    }
    const ChunkOctree *chunk_octree = zox_get(chunk, ChunkOctree)
    if (!chunk_octree) {
        return;
    }
    byte3 voxel_position_local = get_local_position_byte3(voxel_position, chunk_position, default_chunk_size_byte3);
    if (!byte3_in_bounds(voxel_position_local, default_chunk_size_byte3)) {
        return;
    }
    const byte voxel = get_octree_voxel(chunk_octree, &voxel_position_local, max_octree_depth);
    if (block_collisions[voxel]) {
        *collided_d = 1 + is_negative;
        *distance_d = offset_d;
    }
}

// macros

#define handle_collision_axis_d2(d1, d2, offset_d1, offset_d2, is_negative1, is_negative2) collide_with_chunk_d2(chunkLinks, block_collisions, real_position_to_voxel_position(position_last), zox_axis##_##d1, collision_point_real.d1, position_last.d1, offset_d1, &did_collide##_##d1, &collision_offset.d1, is_negative1, zox_axis##_##d2, collision_point_real.d2, position_last.d2, offset_d2, &did_collide##_##d2, &collision_offset.d2, is_negative2);

#define handle_collision_axis(d, offset, is_negative) collide_with_chunk(chunkLinks, block_collisions, real_position_to_voxel_position(position_last), zox_axis##_##d, collision_point_real.d,  position_last.d, offset.d, &did_collide##_##d, &collision_offset.d, is_negative);

#define detect_voxel_collisions()\
\
const float3 offset_left = float3_multiply_float(bounds3D->value, -1);\
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
