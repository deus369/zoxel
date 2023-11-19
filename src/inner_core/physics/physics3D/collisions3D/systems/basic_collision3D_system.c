const float collision_precision = 1.0f; // 0.99f; // 0.999f;    // 9
const float terrain_voxel_scale_inverse = 1 / 0.5f;
const float grounded_velocity_threshold = 0.22f;
// const float terrain_voxel_scale = 0.5f;
const float lowest_velocity_threshold = 0.03f; // 0.3 // 0.001
// draw line to voxel side from character...

#define handle_collision_axis(d, offset) {\
    float3 collision_point_last2 = collision_point_last;\
    collision_point_last2.d += offset.d;\
    int3 last_global_voxel_position = get_voxel_position(collision_point_last2);\
    float3 collision_point = collision_point_last;\
    collision_point.d = collision_point_real.d + offset.d;\
    int3 global_voxel_position_axis = get_voxel_position(collision_point);\
    if (global_voxel_position_axis.d != last_global_voxel_position.d) {\
        int3 chunk_position = get_chunk_position(collision_point, default_chunk_size);\
        ecs_entity_t chunk_axis = int3_hash_map_get(chunkLinks->value, chunk_position);\
        const ChunkOctree *chunkOctree = zox_get(chunk_axis, ChunkOctree)\
        if (chunkOctree) {\
            byte3 local_voxel_position_axis = get_local_position_byte3(global_voxel_position_axis, chunkPosition->value, default_chunk_size_byte3);\
            if (local_voxel_position_axis.x < default_chunk_length && local_voxel_position_axis.y < default_chunk_length && local_voxel_position_axis.z < default_chunk_length) {\
                unsigned char voxel_axis = get_octree_voxel(chunkOctree, &local_voxel_position_axis, max_octree_depth);\
                if (voxel_axis) {\
                    did_collide##_##d = 1;\
                    collision_offset.d = offset.d;\
                }\
            }\
        }\
    }\
}

#define respond_collision(d) {\
    if (did_collide##_##d) {\
        float3 collision_point = collision_point_last;\
        collision_point.d += collision_offset.d;\
        float scaled_voxel_point = collision_point.d * terrain_voxel_scale_inverse;\
        float voxel_side_position = 0;\
        if (position_delta.d <= 0) voxel_side_position = floor(scaled_voxel_point);\
        else voxel_side_position = ceil(scaled_voxel_point);\
        float distance_to_voxel_side = scaled_voxel_point - voxel_side_position;\
        distance_to_voxel_side /= terrain_voxel_scale_inverse;\
        position3D->value.d = collision_point_last.d - distance_to_voxel_side;\
        velocity3D->value.d *= -bounce_lost_force;\
    }\
}

void BasicCollision3DSystem(ecs_iter_t *it) {
    ecs_world_t *world = it->world;
    const VoxLink *voxLinks = ecs_field(it, VoxLink, 1);
    const Bounds3D *bounds3Ds = ecs_field(it, Bounds3D, 8);
    ChunkPosition *chunkPositions = ecs_field(it, ChunkPosition, 2);
    Position3D *position3Ds = ecs_field(it, Position3D, 3);
    Velocity3D *velocity3Ds = ecs_field(it, Velocity3D, 4);
    // VoxelPosition *voxelPositions = ecs_field(it, VoxelPosition, 5);
    // ChunkLink *chunkLinks = ecs_field(it, ChunkLink, 6);
    LastPosition3D *lastPosition3Ds = ecs_field(it, LastPosition3D, 7);
    Grounded *groundeds = ecs_field(it, Grounded, 9);
    for (int i = 0; i < it->count; i++) {
        const ecs_entity_t e = it->entities[i];
        const Bounds3D *bounds3D = &bounds3Ds[i];
        ChunkPosition *chunkPosition = &chunkPositions[i];
        // todo: check chunklink or neighbors instead of hashmap checking
        // ChunkLink *chunkLink = &chunkLinks[i];
        Position3D *position3D = &position3Ds[i];
        LastPosition3D *lastPosition3D = &lastPosition3Ds[i];
        // VoxelPosition *voxelPosition = &voxelPositions[i];
        Grounded *grounded = &groundeds[i];
        // byte3 old_voxel_position = int3_to_byte3(voxelPosition->value);
        float3 collision_point_real = position3D->value;
        float3 collision_point_last = lastPosition3D->value;
        float3 position_delta = float3_subtract_float3(collision_point_real, collision_point_last);
        {
            // actually here I should check if makes it through to new voxel_position
#ifdef zoxel_debug_basic_collision3D_system
            if (voxelPosition->value.x >= default_chunk_length || voxelPosition->value.y >= default_chunk_length || voxelPosition->value.z >= default_chunk_length) {
                zoxel_log(" !!! voxel position set out of bounds !!!\n");
                zoxel_log(" !> chunk_position [%ix%ix%i]\n", chunk_position.x, chunk_position.y, chunk_position.z);
                zoxel_log("     !+ global voxel position [%ix%ix%i]\n", global_voxel_position.x, global_voxel_position.y, global_voxel_position.z);
                zoxel_log("     !+ local voxel position [%ix%ix%i]\n", new_position.x, new_position.y, new_position.z);
                zoxel_log("     !+ real position [%fx%fx%f]\n", collision_point_real.x, collision_point_real.y, collision_point_real.z);
            } else {
                zoxel_log(" > chunk_position [%ix%ix%i]\n", chunkPosition->value.x, chunkPosition->value.y, chunkPosition->value.z);
                zoxel_log("     + voxel position updated [%ix%ix%i]\n", new_position.x, new_position.y, new_position.z);
                zoxel_log("     + global voxel position [%ix%ix%i]\n", global_voxel_position.x, global_voxel_position.y, global_voxel_position.z);
                zoxel_log("     + real position was [%fx%fx%f]\n", collision_point_real.x, collision_point_real.y, collision_point_real.z);
            }
#endif
            const VoxLink *voxLink = &voxLinks[i];
            if (!voxLink->value) continue;
            const ChunkLinks *chunkLinks = zox_get(voxLink->value, ChunkLinks)
            if (!chunkLinks) continue;
            Velocity3D *velocity3D = &velocity3Ds[i];
            unsigned char did_collide_x = 0;
            unsigned char did_collide_y = 0;
            unsigned char did_collide_z = 0;
            float3 offset_left = float3_multiply_float(bounds3D->value, -1);
            float3 offset_right = bounds3D->value;
            float3 collision_offset = float3_zero;
            handle_collision_axis(x, offset_left)
            handle_collision_axis(y, offset_left)
            handle_collision_axis(z, offset_left)
            if (!did_collide_x) handle_collision_axis(x, offset_right)
            if (!did_collide_y) handle_collision_axis(y, offset_right)
            if (!did_collide_z) handle_collision_axis(z, offset_right)
            respond_collision(x)
            respond_collision(y)
            respond_collision(z)
            // set voxel / chunk position
            /*int3 new_global_voxel_position = get_voxel_position(position3D->value);
            int3 new_chunk_position = get_chunk_position(position3D->value, default_chunk_size);
            byte3 new_local_voxel_position = get_local_position_byte3(new_global_voxel_position, new_chunk_position, default_chunk_size_byte3);
            if (!int3_equals(chunkPosition->value, new_chunk_position)) {
                voxelPosition->value = byte3_to_int3(new_local_voxel_position);
                chunkPosition->value = new_chunk_position;
                set_entity_chunk(world, e, chunkLink, int3_hash_map_get(chunkLinks->value, new_chunk_position));
                // chunkLink->value = int3_hash_map_get(chunkLinks->value, new_chunk_position);
            }*/
            if (did_collide_y) {
                // voxelPosition->value = byte3_to_int3(local_voxel_position);
                if (float_abs(velocity3D->value.y) < grounded_velocity_threshold) {
                    if (!grounded->value) {
                        if (!zox_has(e, Jump) || !zox_gett_value(e, Jump)) {
                            grounded->value = 1;
#ifdef zox_log_jumping
                            zoxel_log(" > grounded [%lu] again (%f)\n", e, zox_current_time);
#endif
                        }
                    }
                }
#ifdef zoxel_debug_basic_collision3D_system
                if (voxelPosition->value.x >= default_chunk_length || voxelPosition->value.y >= default_chunk_length || voxelPosition->value.z >= default_chunk_length) {
                    zoxel_log(" !!! voxel position set out of bounds\n");
                    zoxel_log(" ! > chunk_position [%ix%ix%i]\n", chunkPosition->value.x, chunkPosition->value.y, chunkPosition->value.z);
                    zoxel_log("     ! + voxel position updated [%ix%ix%i]\n", new_position.x, new_position.y, new_position.z);
                    zoxel_log("     ! + real position was [%fx%fx%f]\n", collision_point_real.x, collision_point_real.y, collision_point_real.z);
                }
#endif
            }
            lastPosition3D->value = position3D->value;
        }
    }
} zox_declare_system(BasicCollision3DSystem)
                    
/*int3 new_chunk_position = get_chunk_position(collision_point_real, default_chunk_size);
if (!int3_equals(chunkPosition->value, new_chunk_position)) {
    chunkPosition->value = new_chunk_position;
    set_entity_chunk(world, it->entities[i], chunkLink, int3_hash_map_get(chunkLinks->value, new_chunk_position));
    // chunkLink->value = int3_hash_map_get(chunkLinks->value, new_chunk_position);
}*/
// int3 new_global_voxel_position = get_voxel_position(collision_point_real);
// byte3 new_voxel_position = get_local_position_byte3(new_global_voxel_position, chunkPosition->value, default_chunk_size_byte3);

/*
float3 position_axis_x = collision_point_last;
position_axis_x.x = position3D->value.x;
int3 global_voxel_position_x = get_voxel_position(position_axis_x);
byte3 local_voxel_position_x = get_local_position_byte3(global_voxel_position_x, chunkPosition->value, default_chunk_size_byte3);
if (local_voxel_position_x.x != old_voxel_position.x) {
    unsigned char voxel_x = get_octree_voxel(chunkOctree, &local_voxel_position_x, max_octree_depth);
    if (voxel_x != 0) {
        #ifdef zoxel_debug_basic_collision3D_system
            zoxel_log("     + collision X [%i move to %i]\n", old_voxel_position.x, local_voxel_position_x.x);
        #endif
        position3D->value.x -= velocity3D->value.x * delta_time * bounce_multiplier;
        velocity3D->value.x *= -bounce_lost_force;
        voxelPosition->value.x = old_voxel_position.x;
    }
}

float3 position_axis_y = collision_point_last;
position_axis_y.y = position3D->value.y;
int3 global_voxel_position_y = get_voxel_position(position_axis_y);
byte3 local_voxel_position_y = get_local_position_byte3(global_voxel_position_y, chunkPosition->value, default_chunk_size_byte3);
if (local_voxel_position_y.y != old_voxel_position.y) {
    unsigned char voxel_y = get_octree_voxel(chunkOctree, &local_voxel_position_y, max_octree_depth);
    if (voxel_y != 0) {
        #ifdef zoxel_debug_basic_collision3D_system
            zoxel_log("     + collision Y [%i move to %i]\n", old_voxel_position.y, local_voxel_position_y.y);
        #endif
        position3D->value.y -= velocity3D->value.y * delta_time * bounce_multiplier;
        velocity3D->value.y *= -bounce_lost_force;
        voxelPosition->value.y = old_voxel_position.y;
    }
}

float3 position_axis_z = collision_point_last;
position_axis_z.z = position3D->value.z;
int3 global_voxel_position_z = get_voxel_position(position_axis_z);
byte3 local_voxel_position_z = get_local_position_byte3(global_voxel_position_z, chunkPosition->value, default_chunk_size_byte3);
if (local_voxel_position_z.z != old_voxel_position.z) {
    unsigned char voxel_z = get_octree_voxel(chunkOctree, &local_voxel_position_z, max_octree_depth);
    if (voxel_z != 0) {
        #ifdef zoxel_debug_basic_collision3D_system
            zoxel_log("     + collision Z [%i move to %i]\n", old_voxel_position.z, local_voxel_position_z.z);
        #endif
        position3D->value.z -= velocity3D->value.z * delta_time * bounce_multiplier;
        velocity3D->value.z *= -bounce_lost_force;
        voxelPosition->value.z = old_voxel_position.z;
    }
}
*/
// check each axis delta position change  
/*byte3 voxel_position_2 = (byte3) { voxelPosition->value.x, voxelPosition->value.y, voxelPosition->value.z };
// uhh this..? checking local bounds i think
if (voxel_position_2.x < default_chunk_length && voxel_position_2.y < default_chunk_length && voxel_position_2.z < default_chunk_length) {
    unsigned char voxel = get_octree_voxel(chunkOctree, &voxel_position_2, max_octree_depth);
    #ifdef zoxel_debug_basic_collision3D_system
        zoxel_log(" > voxel %i\n", voxel);
    #endif
    // if voxel is solid, reset positin to last position, by subtracting velocity
    if (voxel != 0) {
        #ifdef zoxel_debug_basic_collision3D_system
            zoxel_log(" > voxel collided %i\n", voxel);
        #endif
        if (old_voxel_position.y != voxelPosition->value.y) {
            position3D->value.y -= velocity3D->value.y * delta_time * bounce_multiplier;
            velocity3D->value.y *= -bounce_lost_force;
            voxelPosition->value.y = old_voxel_position.y;
        }
        // get normal of collision here
        #ifndef zoxel_disable_non_vertical_bounce
            if (old_voxel_position.x != voxelPosition->value.x) {
                position3D->value.x -= velocity3D->value.x * delta_time * bounce_multiplier;
                velocity3D->value.x *= -bounce_lost_force;
                voxelPosition->value.x = old_voxel_position.x;
            }
            if (old_voxel_position.z != voxelPosition->value.z) {
                position3D->value.z -= velocity3D->value.z * delta_time * bounce_multiplier;
                velocity3D->value.z *= -bounce_lost_force;
                voxelPosition->value.z = old_voxel_position.z;
            }
        #endif
        // velocity3D->value.y = 0;
        // float3_subtract_float3_p(&position3D->value, velocity3D->value);
        if (position3D->value.y < -256) {
            // zoxel_log(" !!! npc is too far deep %lu\n", it->entities[i]);
            ecs_delete(world, it->entities[i]);
        }
    }
}
#ifdef zoxel_debug_basic_collision3D_system
    else {
        zoxel_log(" > vox has no chunk linked [%lu]\n", it->entities[i]);
    }
#endif*/

            // todo: handle between chunks here, if new voxel is in another chunk
            // i should really displace it based on the difference of how far in the object is into the voxel
            /*if (!did_collide_x && !did_collide_y && !did_collide_z) handle_collision_axis3(x, y, z)
            if (!did_collide_x && !did_collide_y) handle_collision_axis2(x, y)
            if (!did_collide_y && !did_collide_z) handle_collision_axis2(y, z)
            if (!did_collide_x && !did_collide_z) handle_collision_axis2(x, z)
            if (!did_collide_x) handle_collision_axis(x)
            if (!did_collide_y) handle_collision_axis(y)
            if (!did_collide_z) handle_collision_axis(z)
            respond_collision(x)
            respond_collision(y)
            respond_collision(z)*/

/* update collision point for next axis checks */
/*collision_point_last.d = new_position.d;*/
/*float distance_to_voxel_side = collision_point_last.d - voxel_side_position;*/
/*position3D->value.d = voxel_side_position + bounds3D->value.y;*/
/* this moves the voxel_side_position back outside of terrain space */
/*voxel_side_position /= terrain_voxel_scale_inverse;*/
// this would remove shaking!
/*if (float_abs(velocity3D->value.d) < lowest_velocity_threshold) velocity3D->value.d = 0;*/

            // for example if hits axis x first, then maybe check
            // todo: fix collision with multiple axis at once
            // for situation where xy, xz, xz, or xyz
            // todo: here, i shall reposition based on collisions that were detected, x, y, z, xy, xz, yz, xyz, 7 combinations

/*
// 2 dimensional axis collision detection
#define handle_collision_axis3(d1, d2, d3) {\
    float3 new_position = collision_point_real;\
    int3 global_voxel_position_axis = get_voxel_position(new_position);\
    if (global_voxel_position_axis.d1 != last_global_voxel_position.d1 && global_voxel_position_axis.d2 != last_global_voxel_position.d2 && global_voxel_position_axis.d3 != last_global_voxel_position.d3) {\
        int3 chunk_position = get_chunk_position(new_position, default_chunk_size);\
        ecs_entity_t chunk_axis = int3_hash_map_get(chunkLinks->value, chunk_position);\
        const ChunkOctree *chunkOctree = zox_get(chunk_axis, ChunkOctree)\
        if (chunkOctree) {\
            byte3 local_voxel_position_axis = get_local_position_byte3(global_voxel_position_axis, chunkPosition->value, default_chunk_size_byte3);\
            if (local_voxel_position_axis.x < default_chunk_length && local_voxel_position_axis.y < default_chunk_length && local_voxel_position_axis.z < default_chunk_length) {\
                unsigned char voxel_axis = get_octree_voxel(chunkOctree, &local_voxel_position_axis, max_octree_depth);\
                if (voxel_axis) {\
                    did_collide##_##d1 = 1;\
                    did_collide##_##d2 = 1;\
                    did_collide##_##d3 = 1;\
                }\
            }\
        }\
    }\
}

// 2 dimensional axis collision detection
#define handle_collision_axis2(d1, d2) {\
    float3 new_position = collision_point_last;\
    new_position.d1 = collision_point_real.d1;\
    new_position.d2 = collision_point_real.d2;\
    int3 global_voxel_position_axis = get_voxel_position(new_position);\
    if (global_voxel_position_axis.d1 != last_global_voxel_position.d1 && global_voxel_position_axis.d2 != last_global_voxel_position.d2) {\
        int3 chunk_position = get_chunk_position(new_position, default_chunk_size);\
        ecs_entity_t chunk_axis = int3_hash_map_get(chunkLinks->value, chunk_position);\
        const ChunkOctree *chunkOctree = zox_get(chunk_axis, ChunkOctree)\
        if (chunkOctree) {\
            byte3 local_voxel_position_axis = get_local_position_byte3(global_voxel_position_axis, chunkPosition->value, default_chunk_size_byte3);\
            if (local_voxel_position_axis.x < default_chunk_length && local_voxel_position_axis.y < default_chunk_length && local_voxel_position_axis.z < default_chunk_length) {\
                unsigned char voxel_axis = get_octree_voxel(chunkOctree, &local_voxel_position_axis, max_octree_depth);\
                if (voxel_axis) {\
                    did_collide##_##d1 = 1;\
                    did_collide##_##d2 = 1;\
                }\
            }\
        }\
    }\
}*/

// todo: time this function
// done seperated voxel position, and chunk position updates outside of this
// done check normal of voxel position difference, base bounce velocity off that instead of just y axis
// zoxel_log(" distance_to_voxel_side [%f]\n", distance_to_voxel_side);
// zoxel_log(" distance_to_voxel_side [%f] - new pos [%f] - last [%f -> %f]\n", distance_to_voxel_side, position3D->value.d, collision_point_real.d, collision_point_last.d);
// the 0.5f scale should be based on terrain voxel scale

// collision_point_real.y -= bounds3D->value.y;
// collision_point_last.y -= bounds3D->value.y;
// int3 global_voxel_position = get_voxel_position(collision_point_real);
// int3 last_global_voxel_position = get_voxel_position(collision_point_last);
// int3 chunk_position = get_chunk_position(collision_point_real, default_chunk_size);
// byte3 local_voxel_position = get_local_position_byte3(global_voxel_position, chunk_position, default_chunk_size_byte3);
// if (!byte3_equals(local_voxel_position, old_voxel_position))

            // voxelPosition->value = byte3_to_int3(local_voxel_position);
            // todo: here declare voxel dimensions, side positions?
            // get last position
