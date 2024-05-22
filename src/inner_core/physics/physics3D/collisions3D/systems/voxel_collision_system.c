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
void collide_with_chunk_d3(const ChunkLinks *chunk_links, int3 voxel_position,
    const unsigned char axis_d1, float position_d1, float position_last_d1, const float offset_d1, unsigned char *collided_d1, float *distance_d1, const unsigned char is_negative1,
    const unsigned char axis_d2, float position_d2, float position_last_d2, const float offset_d2, unsigned char *collided_d2, float *distance_d2, const unsigned char is_negative2,
    const unsigned char axis_d3, float position_d3, float position_last_d3, const float offset_d3, unsigned char *collided_d3, float *distance_d3, const unsigned char is_negative3) {

    if (*collided_d1 || *collided_d2 || *collided_d3) return;

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

    if (position_vox_d1 == position_vox_last_d1 && position_vox_d2 == position_vox_last_d2 && position_vox_d3 == position_vox_last_d3) return;

    // Set dimensional variables to newer points
    int3_set_d(&voxel_position, axis_d1, position_vox_d1);
    int3_set_d(&voxel_position, axis_d2, position_vox_d2);
    int3_set_d(&voxel_position, axis_d3, position_vox_d3);

    // Convert real to voxel grid space and check voxel
    const int3 chunk_position = voxel_position_to_chunk_position(voxel_position, default_chunk_size);
    const ecs_entity_t chunk = int3_hash_map_get(chunk_links->value, chunk_position);
    const ChunkOctree *chunk_octree = zox_get(chunk, ChunkOctree);
    if (!chunk_octree) return;

    byte3 voxel_position_local = get_local_position_byte3(voxel_position, chunk_position, default_chunk_size_byte3);
    if (!byte3_in_bounds(voxel_position_local, default_chunk_size_byte3)) return;

    const unsigned char voxel = get_octree_voxel(chunk_octree, &voxel_position_local, max_octree_depth);
    if (voxel) {
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
    collide_with_chunk_d3(chunkLinks, real_position_to_voxel_position(last_position), \
    zox_axis##_##d1, collision_point_real.d1, last_position.d1, offset_d1, &did_collide##_##d1, &collision_offset.d1, is_negative1, \
    zox_axis##_##d2, collision_point_real.d2, last_position.d2, offset_d2, &did_collide##_##d2, &collision_offset.d2, is_negative2, \
    zox_axis##_##d3, collision_point_real.d3, last_position.d3, offset_d3, &did_collide##_##d3, &collision_offset.d3, is_negative3);


// expand previous function by second dimension
void collide_with_chunk_d2(const ChunkLinks *chunk_links, int3 voxel_position, const unsigned char axis_d1, float position_d1, float position_last_d1, const float offset_d1, unsigned char *collided_d1, float *distance_d1, const unsigned char is_negative1, const unsigned char axis_d2, float position_d2, float position_last_d2, const float offset_d2, unsigned char *collided_d2, float *distance_d2, const unsigned char is_negative2) {

    if (*collided_d1 || *collided_d2) return;

    position_last_d1 += offset_d1;
    position_last_d2 += offset_d2;
    position_d1 += offset_d1;
    position_d2 += offset_d2;

    const int position_vox_last_d1 = real_position_to_voxel_position_dim(position_last_d1);
    const int position_vox_last_d2 = real_position_to_voxel_position_dim(position_last_d2);
    const int position_vox_d1 = real_position_to_voxel_position_dim(position_d1);
    const int position_vox_d2 = real_position_to_voxel_position_dim(position_d2);
    if (position_vox_d1 == position_vox_last_d1 && position_vox_d2 == position_vox_last_d2) return;

    int3_set_d(&voxel_position, axis_d1, position_vox_d1);
    int3_set_d(&voxel_position, axis_d2, position_vox_d2);

    const int3 chunk_position = voxel_position_to_chunk_position(voxel_position, default_chunk_size);
    const ecs_entity_t chunk = int3_hash_map_get(chunk_links->value, chunk_position);
    const ChunkOctree *chunk_octree = zox_get(chunk, ChunkOctree)
    if (!chunk_octree) return;

    byte3 voxel_position_local = get_local_position_byte3(voxel_position, chunk_position, default_chunk_size_byte3);
    if (!byte3_in_bounds(voxel_position_local, default_chunk_size_byte3)) return;

    const unsigned char voxel = get_octree_voxel(chunk_octree, &voxel_position_local, max_octree_depth);
    if (voxel) {
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

void collide_with_chunk(const ChunkLinks *chunk_links, int3 voxel_position, const unsigned char axis_d, float position_d, float position_last_d, const float offset_d, unsigned char *collided_d, float *distance_d, const unsigned char is_negative) {

    if (*collided_d) return;

    // firstt  we get our intersection line! (two points)
    position_last_d += offset_d;
    position_d += offset_d;

    const int position_vox_last_d = real_position_to_voxel_position_dim(position_last_d);
    const int position_vox_d = real_position_to_voxel_position_dim(position_d);
    if (position_vox_d == position_vox_last_d) return;
    // set dimensional variables to newer point
    int3_set_d(&voxel_position, axis_d, position_vox_d);

    // next convert real to voxel grid space and check voxel
    const int3 chunk_position = voxel_position_to_chunk_position(voxel_position, default_chunk_size);
    const ecs_entity_t chunk = int3_hash_map_get(chunk_links->value, chunk_position);
    const ChunkOctree *chunk_octree = zox_get(chunk, ChunkOctree)
    if (!chunk_octree) return;

    byte3 voxel_position_local = get_local_position_byte3(voxel_position, chunk_position, default_chunk_size_byte3);
    if (!byte3_in_bounds(voxel_position_local, default_chunk_size_byte3)) return;

    const unsigned char voxel = get_octree_voxel(chunk_octree, &voxel_position_local, max_octree_depth);
    if (voxel) {
        *collided_d = 1 + is_negative;
        *distance_d = offset_d;
    }
}

// macros

#define handle_collision_axis_d2(d1, d2, offset_d1, offset_d2, is_negative1, is_negative2) collide_with_chunk_d2(chunkLinks,  real_position_to_voxel_position(last_position), zox_axis##_##d1, collision_point_real.d1, last_position.d1, offset_d1, &did_collide##_##d1, &collision_offset.d1, is_negative1, zox_axis##_##d2, collision_point_real.d2, last_position.d2, offset_d2, &did_collide##_##d2, &collision_offset.d2, is_negative2);

#define handle_collision_axis(d, offset, is_negative) collide_with_chunk(chunkLinks, real_position_to_voxel_position(last_position), zox_axis##_##d, collision_point_real.d,  last_position.d, offset.d, &did_collide##_##d, &collision_offset.d, is_negative);


// responding
// draw line for collided voxels
extern void render_line3D(ecs_world_t *world, const float3 a, const float3 b, const color_rgb line_color);

#define respond_collision(d) {\
    if (did_collide##_##d) {\
        float3 voxel_normal = float3_zero;\
        voxel_normal.d = 1;\
        if (did_collide##_##d == 1) voxel_normal.d *= -1;\
        float3 collision_point = last_position;\
        collision_point.d = position_new.d + collision_offset.d;\
        /* convert real position to voxel one */\
        float voxel_side_position = 0;\
        if (did_collide##_##d == 1) voxel_side_position = floor(collision_point.d * terrain_voxel_scale_inverse) / terrain_voxel_scale_inverse;\
        else voxel_side_position = ceil(collision_point.d * terrain_voxel_scale_inverse) / terrain_voxel_scale_inverse;\
        /* convert real position to voxel one */\
        float delta = collision_point.d - voxel_side_position;\
        position3D->value.d = position_new.d - delta;\
        velocity3D->value.d *= -bounce_lost_force;\
        if (zox_debug_collision_response.d) render_line3D(world, collision_point, float3_add(collision_point, voxel_normal), color_rgb_white);\
        /*if (is_log) zox_log(" + at [%f] bob [%f] voxel [%f] delta distance [%f] normal [%f]\n", zox_current_time, collision_point.d, voxel_side_position, delta, voxel_normal.d)*/\
    }\
}

// for a collision 3D box
void VoxelCollisionSystem(ecs_iter_t *it) {
    zox_iter_world()
    zox_field_in(VoxLink, voxLinks, 1)
    zox_field_in(ChunkPosition, chunkPositions, 2)
    zox_field_out(Position3D, position3Ds, 3)
    zox_field_out(Velocity3D, velocity3Ds, 4)
    zox_field_out(LastPosition3D, lastPosition3Ds, 5)
    zox_field_in(Bounds3D, bounds3Ds, 6)
    zox_field_out(Grounded, groundeds, 7)
    for (int i = 0; i < it->count; i++) {
        zox_field_i_in(Bounds3D, bounds3Ds, bounds3D)
        zox_field_i_in(VoxLink, voxLinks, voxLink)
        zox_field_i_in(ChunkPosition, chunkPositions, chunkPosition)
        zox_field_i_out(Position3D, position3Ds, position3D)
        zox_field_i_out(Velocity3D, velocity3Ds, velocity3D)
        zox_field_i_out(LastPosition3D, lastPosition3Ds, lastPosition3D)
        zox_field_i_out(Grounded, groundeds, grounded)
        // actually here I should check if makes it through to new voxel_position
#ifdef zoxel_debug_basic_collision3D_system
        if (voxelPosition->value.x >= default_chunk_length || voxelPosition->value.y >= default_chunk_length || voxelPosition->value.z >= default_chunk_length) {
            zox_log(" !!! voxel position set out of bounds !!!\n");
            zox_log(" !> chunk_position [%ix%ix%i]\n", chunk_position.x, chunk_position.y, chunk_position.z);
            zox_log("     !+ global voxel position [%ix%ix%i]\n", global_voxel_position.x, global_voxel_position.y, global_voxel_position.z);
            zox_log("     !+ local voxel position [%ix%ix%i]\n", new_position.x, new_position.y, new_position.z);
            zox_log("     !+ real position [%fx%fx%f]\n", collision_point_real.x, collision_point_real.y, collision_point_real.z);
        } else {
            zox_log(" > chunk_position [%ix%ix%i]\n", chunkPosition->value.x, chunkPosition->value.y, chunkPosition->value.z);
            zox_log("     + voxel position updated [%ix%ix%i]\n", new_position.x, new_position.y, new_position.z);
            zox_log("     + global voxel position [%ix%ix%i]\n", global_voxel_position.x, global_voxel_position.y, global_voxel_position.z);
            zox_log("     + real position was [%fx%fx%f]\n", collision_point_real.x, collision_point_real.y, collision_point_real.z);
        }
#endif
        if (!voxLink->value || !zox_alive(voxLink->value)) continue; // these shouldn't be here
        const ChunkLinks *chunkLinks = zox_get(voxLink->value, ChunkLinks)
        if (!chunkLinks) continue;
        const unsigned char is_falling = velocity3D->value.y < 0;
        unsigned char did_collide_x = 0;
        unsigned char did_collide_y = 0;
        unsigned char did_collide_z = 0;
        const float3 offset_left = float3_multiply_float(bounds3D->value, -1);
        const float3 offset_right = bounds3D->value;
        // const float3 position_delta = float3_subtract_float3(position3D->value, lastPosition3D->value);
        const float3 last_position = lastPosition3D->value;
        const float3 position_new = position3D->value;
        float3 collision_point_real = position3D->value;
        float3 collision_offset = float3_zero;

        // single axis collision, two sides per axis
        handle_collision_axis(x, offset_left, 1)
        handle_collision_axis(x, offset_right, 0)
        handle_collision_axis(y, offset_left, 1)
        handle_collision_axis(y, offset_right, 0)
        handle_collision_axis(z, offset_left, 1)
        handle_collision_axis(z, offset_right, 0)

        // double axis collision, fours sides per two axis
        // x z
        handle_collision_axis_d2(x, z, offset_left.x, offset_left.z, 1, 1)
        handle_collision_axis_d2(x, z, offset_right.x, offset_left.z, 0, 1)
        handle_collision_axis_d2(x, z, offset_left.x, offset_right.z, 1, 0)
        handle_collision_axis_d2(x, z, offset_right.x, offset_right.z, 0, 0)
        // x y
        handle_collision_axis_d2(x, y, offset_left.x, offset_left.y, 1, 1)
        handle_collision_axis_d2(x, y, offset_right.x, offset_left.y, 0, 1)
        handle_collision_axis_d2(x, y, offset_left.x, offset_right.y, 1, 0)
        handle_collision_axis_d2(x, y, offset_right.x, offset_right.y, 0, 0)
        // z y
        handle_collision_axis_d2(z, y, offset_left.z, offset_left.y, 1, 1)
        handle_collision_axis_d2(z, y, offset_right.z, offset_left.y, 0, 1)
        handle_collision_axis_d2(z, y, offset_left.z, offset_right.y, 1, 0)
        handle_collision_axis_d2(z, y, offset_right.z, offset_right.y, 0, 0)

        // three axis collision
        // handle_collision_axis_d3(x, y, z, offset_left.x, offset_left.y, 1, 1, 1)
        handle_collision_axis_d3(x, y, z, offset_left.x, offset_left.y, offset_left.z, 1, 1, 1)
        handle_collision_axis_d3(x, y, z, offset_right.x, offset_left.y, offset_left.z, 0, 1, 1)
        handle_collision_axis_d3(x, y, z, offset_left.x, offset_right.y, offset_left.z, 1, 0, 1)
        handle_collision_axis_d3(x, y, z, offset_right.x, offset_right.y, offset_left.z, 0, 0, 1)
        handle_collision_axis_d3(x, y, z, offset_left.x, offset_left.y, offset_right.z, 1, 1, 0)
        handle_collision_axis_d3(x, y, z, offset_right.x, offset_left.y, offset_right.z, 0, 1, 0)
        handle_collision_axis_d3(x, y, z, offset_left.x, offset_right.y, offset_right.z, 1, 0, 0)
        handle_collision_axis_d3(x, y, z, offset_right.x, offset_right.y, offset_right.z, 0, 0, 0)


        // respond to collisions
        respond_collision(x)
        respond_collision(y)
        respond_collision(z)

        grounded->value = (did_collide_y && is_falling);
        lastPosition3D->value = position3D->value;
#ifdef zoxel_debug_basic_collision3D_system
        if (did_collide_y && voxelPosition->value.x >= default_chunk_length || voxelPosition->value.y >= default_chunk_length || voxelPosition->value.z >= default_chunk_length) {
            zox_log(" !!! voxel position set out of bounds\n");
            zox_log(" ! > chunk_position [%ix%ix%i]\n", chunkPosition->value.x, chunkPosition->value.y, chunkPosition->value.z);
            zox_log("     ! + voxel position updated [%ix%ix%i]\n", new_position.x, new_position.y, new_position.z);
            zox_log("     ! + real position was [%fx%fx%f]\n", collision_point_real.x, collision_point_real.y, collision_point_real.z);
        }
#endif
    }
} zox_declare_system(VoxelCollisionSystem)


// is_nagive = position_delta.d <= 0
// returns axis position to last and bounces velocity
/*#define respond_collision(d) {\
    if (did_collide##_##d) {\
        float3 collision_point = last_position;\
        collision_point.d += collision_offset.d;\
        float scaled_voxel_point = collision_point.d * terrain_voxel_scale_inverse;\
        float voxel_side_position = 0;\
        if (did_collide##_##d == 2) voxel_side_position = floor(scaled_voxel_point);\
        else voxel_side_position = ceil(scaled_voxel_point);\
        float distance_to_voxel_side = scaled_voxel_point - voxel_side_position;\
        distance_to_voxel_side /= terrain_voxel_scale_inverse;\
        position3D->value.d = last_position.d - distance_to_voxel_side;\
        velocity3D->value.d *= -bounce_lost_force;\
    }\
}*/

/*#define handle_collision_axis(d, offset) {\
    float3 collision_point_last2 = collision_point_last;\
    collision_point_last2.d += offset.d;\
    int3 last_global_voxel_position = real_position_to_voxel_position(collision_point_last2);\
    float3 collision_point = collision_point_last;\
    collision_point.d = collision_point_real.d + offset.d;\
    int3 voxel_position = real_position_to_voxel_position(collision_point);\
    if (voxel_position.d != last_global_voxel_position.d) {\
        \
        const int3 chunk_position = real_position_to_chunk_position(collision_point, default_chunk_size);\
        ecs_entity_t chunk_axis = int3_hash_map_get(chunkLinks->value, chunk_position);\
        const ChunkOctree *chunk_octree = zox_get(chunk_axis, ChunkOctree)\
        if (chunk_octree) {\
            byte3 voxel_position_local = get_local_position_byte3(voxel_position, chunkPosition->value, default_chunk_size_byte3);\
            if (byte3_in_bounds(voxel_position_local, default_chunk_size_byte3)) {\
                unsigned char voxel_axis = get_octree_voxel(chunk_octree, &voxel_position_local, max_octree_depth);\
                if (voxel_axis) {\
                    did_collide##_##d = 1;\
                    collision_offset.d = offset.d;\
                }\
            }\
        }\
    }\
}*/

/*int3 chunk_position = voxel_position_to_chunk_position(voxel_position, default_chunk_size);*/

/*if (local_voxel_position_axis.x < default_chunk_length && local_voxel_position_axis.y < default_chunk_length && local_voxel_position_axis.z < default_chunk_length) {*/
