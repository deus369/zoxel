// todo: time this function
// done seperated voxel position, and chunk position updates outside of this
// done check normal of voxel position difference, base bounce velocity off that instead of just y axis
// zoxel_log(" dimension_delta [%f]\n", dimension_delta);
// zoxel_log(" dimension_delta [%f] - new pos [%f] - last [%f -> %f]\n", dimension_delta, position3D->value.d, real_position.d, last_position.d);
// the 0.5f scale should be based on terrain voxel scale
const float collision_precision = 1.0f; // 0.999f;    // 9
const float lowest_velocity_threshold = 0.001f;

#define handle_collision_axis(d) {\
    const float terrain_voxel_scale = 0.5f;\
    const float terrain_voxel_scale_inverse = 1 / terrain_voxel_scale;\
    float3 moved_position = last_position;\
    moved_position.d = real_position.d;\
    int3 chunk_position = get_chunk_position(moved_position, default_chunk_size);\
    ecs_entity_t chunk_axis = int3_hash_map_get(chunkLinks->value, chunk_position);\
    const ChunkOctree *chunkOctree = ecs_get(world, chunk_axis, ChunkOctree);\
    if (chunkOctree == NULL) return;\
    int3 global_voxel_position_axis = get_voxel_position(moved_position);\
    byte3 local_voxel_position_axis = get_local_position_byte3(global_voxel_position_axis, chunkPosition->value, default_chunk_size_byte3);\
    if (local_voxel_position_axis.d != old_voxel_position.d) {\
        if (local_voxel_position_axis.x < default_chunk_length && local_voxel_position_axis.y < default_chunk_length && local_voxel_position_axis.z < default_chunk_length) {\
            unsigned char voxel_axis = get_octree_voxel(chunkOctree, &local_voxel_position_axis, max_octree_depth);\
            if (voxel_axis != 0) {\
                float voxel_side_position = 0;\
                float dimension_delta = real_position.d - last_position.d;\
                if (dimension_delta < 0) voxel_side_position = floor(terrain_voxel_scale_inverse * last_position.d);\
                else voxel_side_position = ceil((float) (terrain_voxel_scale_inverse * last_position.d));\
                dimension_delta = terrain_voxel_scale * ((terrain_voxel_scale_inverse * last_position.d) - voxel_side_position);\
                position3D->value.d = lastPosition3D->value.d - dimension_delta * collision_precision;\
                velocity3D->value.d *= -bounce_lost_force;\
                if (abs(velocity3D->value.d) < lowest_velocity_threshold) velocity3D->value.d = 0.0f;\
                did_collide = 1;\
            }\
        }\
    }\
}

void BasicCollision3DSystem(ecs_iter_t *it) {
    #ifdef zoxel_disable_velocity
        return;
    #endif
    ecs_world_t *world = it->world;
    const VoxLink *voxLinks = ecs_field(it, VoxLink, 1);
    ChunkPosition *chunkPositions = ecs_field(it, ChunkPosition, 2);
    Position3D *position3Ds = ecs_field(it, Position3D, 3);
    Velocity3D *velocity3Ds = ecs_field(it, Velocity3D, 4);
    VoxelPosition *voxelPositions = ecs_field(it, VoxelPosition, 5);
    ChunkLink *chunkLinks = ecs_field(it, ChunkLink, 6);
    LastPosition3D *lastPosition3Ds = ecs_field(it, LastPosition3D, 7);
    const Bounds3D *bounds3Ds = ecs_field(it, Bounds3D, 8);
    for (int i = 0; i < it->count; i++) {
        ChunkPosition *chunkPosition = &chunkPositions[i];
        ChunkLink *chunkLink = &chunkLinks[i];
        Position3D *position3D = &position3Ds[i];
        LastPosition3D *lastPosition3D = &lastPosition3Ds[i];
        VoxelPosition *voxelPosition = &voxelPositions[i];
        const Bounds3D *bounds3D = &bounds3Ds[i];
        byte3 old_voxel_position = int3_to_byte3(voxelPosition->value);
        float3 real_position = position3D->value;
        float3 last_position = lastPosition3D->value;
        real_position.y -= bounds3D->value.y;
        last_position.y -= bounds3D->value.y;
        int3 global_voxel_position = get_voxel_position(real_position);
        int3 chunk_position = get_chunk_position(real_position, default_chunk_size);
        byte3 new_position = get_local_position_byte3(global_voxel_position, chunk_position, default_chunk_size_byte3);
        if (!byte3_equals(new_position, old_voxel_position)) {
            // actually here I should check if makes it through to new voxel_position
            voxelPosition->value = byte3_to_int3(new_position);
            #ifdef zoxel_debug_basic_collision3D_system
                if (voxelPosition->value.x >= default_chunk_length || voxelPosition->value.y >= default_chunk_length || voxelPosition->value.z >= default_chunk_length) {
                    zoxel_log(" !!! voxel position set out of bounds !!!\n");
                    zoxel_log(" !> chunk_position [%ix%ix%i]\n", chunk_position.x, chunk_position.y, chunk_position.z);
                    zoxel_log("     !+ global voxel position [%ix%ix%i]\n", global_voxel_position.x, global_voxel_position.y, global_voxel_position.z);
                    zoxel_log("     !+ local voxel position [%ix%ix%i]\n", new_position.x, new_position.y, new_position.z);
                    zoxel_log("     !+ real position [%fx%fx%f]\n", real_position.x, real_position.y, real_position.z);
                } else {
                    zoxel_log(" > chunk_position [%ix%ix%i]\n", chunkPosition->value.x, chunkPosition->value.y, chunkPosition->value.z);
                    zoxel_log("     + voxel position updated [%ix%ix%i]\n", new_position.x, new_position.y, new_position.z);
                    zoxel_log("     + global voxel position [%ix%ix%i]\n", global_voxel_position.x, global_voxel_position.y, global_voxel_position.z);
                    zoxel_log("     + real position was [%fx%fx%f]\n", real_position.x, real_position.y, real_position.z);
                }
            #endif
            const VoxLink *voxLink = &voxLinks[i];
            if (voxLink->value == 0) continue;
            const ChunkLinks *chunkLinks = ecs_get(world, voxLink->value, ChunkLinks);
            Velocity3D *velocity3D = &velocity3Ds[i];
            // get last position
            unsigned char did_collide = 0;
            // todo: handle between chunks here, if new voxel is in another chunk
            // i should really displace it based on the difference of how far in the object is into the voxel
            handle_collision_axis(y)
            handle_collision_axis(x)
            handle_collision_axis(z)
            lastPosition3D->value = position3D->value;
            int3 new_chunk_position = get_chunk_position(real_position, default_chunk_size);
            if (!int3_equals(chunkPosition->value, new_chunk_position)) {
                chunkPosition->value = new_chunk_position;
                set_entity_chunk(world, it->entities[i], chunkLink, int3_hash_map_get(chunkLinks->value, new_chunk_position));
                // chunkLink->value = int3_hash_map_get(chunkLinks->value, new_chunk_position);
            }
            if (did_collide) {
                voxelPosition->value = byte3_to_int3(new_position);
                if (ecs_has(world, it->entities[i], Grounded) && velocity3D->value.y == 0) {
                    const Jump *jump = ecs_get(world, it->entities[i], Jump);
                    if (jump->value == 0) {
                        Grounded *grounded = ecs_get_mut(world, it->entities[i], Grounded);
                        if (grounded->value == 0) {
                            grounded->value = 1;
                            ecs_modified(world, it->entities[i], Grounded);
                            // velocity3D->value.y *= 0.06f;
                        }
                    }
                }
                #ifdef zoxel_debug_basic_collision3D_system
                    if (voxelPosition->value.x >= default_chunk_length || voxelPosition->value.y >= default_chunk_length || voxelPosition->value.z >= default_chunk_length) {
                        zoxel_log(" !!! voxel position set out of bounds\n");
                        zoxel_log(" ! > chunk_position [%ix%ix%i]\n", chunkPosition->value.x, chunkPosition->value.y, chunkPosition->value.z);
                        zoxel_log("     ! + voxel position updated [%ix%ix%i]\n", new_position.x, new_position.y, new_position.z);
                        zoxel_log("     ! + real position was [%fx%fx%f]\n", real_position.x, real_position.y, real_position.z);
                    }
                #endif
            }
        }
    }
}
zox_declare_system(BasicCollision3DSystem)


/*int3 new_chunk_position = get_chunk_position(real_position, default_chunk_size);
if (!int3_equals(chunkPosition->value, new_chunk_position)) {
    chunkPosition->value = new_chunk_position;
    set_entity_chunk(world, it->entities[i], chunkLink, int3_hash_map_get(chunkLinks->value, new_chunk_position));
    // chunkLink->value = int3_hash_map_get(chunkLinks->value, new_chunk_position);
}*/
// int3 new_global_voxel_position = get_voxel_position(real_position);
// byte3 new_voxel_position = get_local_position_byte3(new_global_voxel_position, chunkPosition->value, default_chunk_size_byte3);

/*
float3 position_axis_x = last_position;
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

float3 position_axis_y = last_position;
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

float3 position_axis_z = last_position;
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
