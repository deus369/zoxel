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
    zox_iter_world()
    zox_field_in(VoxLink, voxLinks, 1)
    zox_field_out(ChunkPosition, chunkPositions, 2)
    zox_field_out(Position3D, position3Ds, 3)
    zox_field_out(Velocity3D, velocity3Ds, 4)
    zox_field_out(LastPosition3D, lastPosition3Ds, 7)
    zox_field_in(Bounds3D, bounds3Ds, 8)
    zox_field_out(Grounded, groundeds, 9)
    for (int i = 0; i < it->count; i++) {
        zox_field_i_in(Bounds3D, bounds3Ds, bounds3D)
        zox_field_i_in(VoxLink, voxLinks, voxLink)
        zox_field_i_out(ChunkPosition, chunkPositions, chunkPosition)
        zox_field_i_out(Position3D, position3Ds, position3D)
        zox_field_i_out(LastPosition3D, lastPosition3Ds, lastPosition3D)
        zox_field_i_out(Grounded, groundeds, grounded)
        const float3 collision_point_real = position3D->value;
        const float3 collision_point_last = lastPosition3D->value;
        const float3 position_delta = float3_subtract_float3(collision_point_real, collision_point_last);
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
        if (!voxLink->value || !ecs_is_alive(world, voxLink->value)) continue; // these shouldn't be here
        const ChunkLinks *chunkLinks = zox_get(voxLink->value, ChunkLinks)
        if (!chunkLinks) continue;
        Velocity3D *velocity3D = &velocity3Ds[i];
        unsigned char did_collide_x = 0;
        unsigned char did_collide_y = 0;
        unsigned char did_collide_z = 0;
        const float3 offset_left = float3_multiply_float(bounds3D->value, -1);
        const float3 offset_right = bounds3D->value;
        float3 collision_offset = float3_zero;
        handle_collision_axis(x, offset_left)
        handle_collision_axis(y, offset_left)
        handle_collision_axis(z, offset_left)
        if (!did_collide_x) handle_collision_axis(x, offset_right)
        if (!did_collide_y) handle_collision_axis(y, offset_right)
        if (!did_collide_z) handle_collision_axis(z, offset_right)
        unsigned char is_falling = velocity3D->value.y < 0;
        respond_collision(x)
        respond_collision(y)
        respond_collision(z)
        grounded->value = 0;
        if (did_collide_y) {
            if (is_falling) grounded->value = 1;
#ifdef zoxel_debug_basic_collision3D_system
            if (voxelPosition->value.x >= default_chunk_length || voxelPosition->value.y >= default_chunk_length || voxelPosition->value.z >= default_chunk_length) {
                zox_log(" !!! voxel position set out of bounds\n");
                zox_log(" ! > chunk_position [%ix%ix%i]\n", chunkPosition->value.x, chunkPosition->value.y, chunkPosition->value.z);
                zox_log("     ! + voxel position updated [%ix%ix%i]\n", new_position.x, new_position.y, new_position.z);
                zox_log("     ! + real position was [%fx%fx%f]\n", collision_point_real.x, collision_point_real.y, collision_point_real.z);
            }
#endif
        }
        lastPosition3D->value = position3D->value;
    }
} zox_declare_system(BasicCollision3DSystem)
