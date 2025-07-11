// Handles AABB to Voxel Chunk Collisions
// todo: support multiple realms - use a hashmap for realms, and cache their data per terrain here
void VoxelCollisionSystem(ecs_iter_t *it) {
    const byte max_depth = terrain_depth;   // todo: use chunk max depths here
    zox_field_world()
    zox_field_in(VoxLink, voxLinks, 1)
    zox_field_out(Position3D, position3Ds, 3)
    zox_field_out(Velocity3D, velocity3Ds, 4)
    zox_field_out(LastPosition3D, lastPosition3Ds, 5)
    zox_field_in(Bounds3D, bounds3Ds, 6)
    zox_field_out(Grounded, groundeds, 7)
    // find realm first
    const VoxelLinks *voxels = get_first_terrain_voxels(world, voxLinks, it->count);
    if (!voxels) {
        return;
    }
    byte block_collisions[voxels->length + 1]; // 255];
    get_block_collisions(world, voxels, block_collisions);

    // now do collisions
    for (int i = 0; i < it->count; i++) {
        zox_field_i(VoxLink, voxLinks, voxLink)
        zox_field_i(Bounds3D, bounds3Ds, bounds3D)
        zox_field_o(Position3D, position3Ds, position3D)
        zox_field_o(Velocity3D, velocity3Ds, velocity3D)
        zox_field_o(LastPosition3D, lastPosition3Ds, lastPosition3D)
        zox_field_o(Grounded, groundeds, grounded)
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
        const float3 position_last = lastPosition3D->value;
        const float3 position_new = position3D->value;
        float3 collision_point_real = position3D->value;
        float3 collision_offset = float3_zero;
        const byte is_falling = velocity3D->value.y < 0;
        byte did_collide_x = 0;
        byte did_collide_y = 0;
        byte did_collide_z = 0;
        detect_voxel_collisions()
        respond_to_collisions()
        // keeps grounded for an additional frame
        if (did_collide_y && is_falling) {
            grounded->value = 1;
        } else {
            if (grounded->value == 1) {
                grounded->value = 2;
            } else {
                grounded->value = 0;
            }
        }
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