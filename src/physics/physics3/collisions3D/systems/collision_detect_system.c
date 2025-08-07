byte collide_with_chunkf(
    ecs *world,
    const ChunkLinks *chunks,
    const byte terrain_depth,
    const float terrain_scale,
    const byte *block_collisions,
    float3 position,
    float3 position_last,
    const float3 offset,
    float *distance_d
) {
    position = float3_add(position, offset);
    position_last = float3_add(position_last, offset);

    // get voxel positions
    const int3 vposition = real_position_to_voxel_position2(position, terrain_scale);
    const int3 vposition_last = real_position_to_voxel_position2(position_last, terrain_scale);
    if (int3_equals(vposition, vposition_last)) {
        return 0;
    }

    const int3 chunk_position = real_position_to_chunk_position(
        position,
        powers_of_two[terrain_depth],
        terrain_scale);
    const entity chunk = int3_hashmap_get(chunks->value, chunk_position);
    if (!zox_valid(chunk)) {
        return 0;
    }

    zox_geter(chunk, VoxelNode, node)
    zox_geter_value(chunk, NodeDepth, byte, node_depth)
    if (!node) {
        return 0;
    }

    byte chunk_length = powers_of_two[terrain_depth];
    const int3 chunk_dimensions = int3_single(chunk_length);
    const byte3 chunk_dimensions_b3 = int3_to_byte3(chunk_dimensions);
    byte3 vposition_local = get_local_position_byte3(
        vposition,
        chunk_dimensions_b3
    );
    if (!byte3_in_bounds(vposition_local, chunk_dimensions_b3)) {
        return 0;
    }

    const byte voxel = get_sub_node_voxel_locked(
        node,
        &vposition_local,
        node_depth);

    if (block_collisions[voxel]) {
        if (offset.x != 0) *distance_d = offset.x;
        else if (offset.y != 0) *distance_d = offset.y;
        else *distance_d = offset.z;
        return 1;
    }
    return 0;
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
        if (!chunks) {
            continue;
        }
        if (collision->value) {
            continue;
        }
        const float3 position_last = lastPosition3D->value;

        /*int3 vpos_last = real_position_to_voxel_position2(
            position_last,
            terrain_scale
        );*/

        float3 collision_point_real = position3D->value;
        float3 collision_distance = float3_zero;
        byte did_collide_x = 0;
        byte did_collide_y = 0;
        byte did_collide_z = 0;

        const float3 offset_left = float3_scale(bounds3D->value, -1);
        const float3 offset_right = bounds3D->value;

        // new detection

        byte collide_down = collide_with_chunkf(
            world,
            chunks,
            terrain_depth,
            terrain_scale,
            block_collisions,
            collision_point_real,
            position_last,
            (float3) { 0, offset_left.y, 0 },
            &collision_distance.y);
        byte collide_up = collide_with_chunkf(
            world,
            chunks,
            terrain_depth,
            terrain_scale,
            block_collisions,
            collision_point_real,
            position_last,
            (float3) { 0, offset_right.y, 0 },
            &collision_distance.y);
        did_collide_y = collide_up ? 1 : (collide_down ? 2 : 0);


        byte collide_left = collide_with_chunkf(
            world,
            chunks,
            terrain_depth,
            terrain_scale,
            block_collisions,
            collision_point_real,
            position_last,
            (float3) { offset_left.x, 0, 0 },
            &collision_distance.x);
        byte collide_right = collide_with_chunkf(
            world,
            chunks,
            terrain_depth,
            terrain_scale,
            block_collisions,
            collision_point_real,
            position_last,
            (float3) { offset_right.x, 0, 0 },
            &collision_distance.x);

        did_collide_x = collide_right ? 1 : (collide_left ? 2 : 0);
        byte collide_back = collide_with_chunkf(
            world,
            chunks,
            terrain_depth,
            terrain_scale,
            block_collisions,
            collision_point_real,
            position_last,
            (float3) { 0, 0, offset_left.z },
            &collision_distance.z);

        byte collide_forward = collide_with_chunkf(
            world,
            chunks,
            terrain_depth,
            terrain_scale,
            block_collisions,
            collision_point_real,
            position_last,
            (float3) { 0, 0, offset_right.z },
            &collision_distance.z);

        did_collide_z = collide_forward ? 1 : (collide_back ? 2 : 0);

        // pack the collision
        if (did_collide_x || did_collide_y || did_collide_z) {
            collisionDistance->value = collision_distance;
            collision->value = (did_collide_x & 0x3) << 0 | (did_collide_y & 0x3) << 2  | (did_collide_z & 0x3) << 4;
        }

    }
} zox_declare_system(CollisionDetectSystem)