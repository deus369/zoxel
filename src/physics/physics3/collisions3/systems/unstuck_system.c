// if character falls through map, push up
// todo: draw lines on this to test why it suddenly detects..!
void UnstuckSystem(iter *it) {
    zox_sys_world()
    zox_sys_begin()
    zox_sys_in(VoxLink)
    zox_sys_in(Bounds3D)
    zox_sys_out(LastUnstuck3)
    zox_sys_out(Position3D)
    // find realm first
    const VoxelLinks *voxels = get_first_terrain_voxels(world, VoxLink_, it->count);
    if (!voxels) {
        return;
    }
    byte colliders[voxels->length + 1];
    get_block_collisions(world, voxels, colliders);
    for (int i = 0; i < it->count; i++) {
        zox_sys_i(VoxLink, voxLink)
        zox_sys_i(Bounds3D, bounds3)
        zox_sys_o(LastUnstuck3, lastUnstuck3)
        zox_sys_o(Position3D, position3)
        zox_geter(voxLink->value, ChunkLinks, chunkLinks)
        zox_geter_value(voxLink->value, VoxScale, float, terrain_scale);
        zox_geter_value(voxLink->value, NodeDepth, byte, terrain_depth);
        const float3 unstuck_push = (float3) { 0, terrain_scale, 0 };

        float3 point = float3_add(position3->value, (float3) { 0, bounds3->value.y / 2.0f, 0 });

        // const float chunk_scale = terrain_scale * ((float) powers_of_two[terrain_depth]);
        const int3 chunk_position = real_position_to_chunk_position(
            point,
            powers_of_two[terrain_depth],
            terrain_scale);

        const entity chunk = int3_hashmap_get(chunkLinks->value, chunk_position);
        if (!zox_valid(chunk)) {
            continue;
        }
        if (!zox_has(chunk, VoxelNode)) {
            zox_log_error("chunk [%s:%lu] doesn't have a VoxelNode!", zox_get_name(chunk), chunk)
            continue;
        }
        zox_geter(chunk, VoxelNode, node);
        zox_geter_value(chunk, NodeDepth, byte, node_depth);
        const byte3 chunk_dimensions_b3 = byte3_single(powers_of_two[node_depth]);
        // positions
        const int3 voxel_position = positionf_to_positionv(point, terrain_scale);
        byte3 voxel_position_local = get_local_position_byte3(voxel_position, chunk_dimensions_b3);
        // voxel
        const byte voxel = get_sub_node_voxel_locked(
            node,
            &voxel_position_local,
            node_depth);
        if (!voxel || !colliders[voxel]) {
            lastUnstuck3->value = position3->value;
            continue;
        }
        if (float3_equals(lastUnstuck3->value, float3_zero)) {
            position3->value = float3_add(position3->value, unstuck_push);
            zox_logw("Character never unstuck v[%ix%ix%i] l[%ix%ix%i]", voxel_position.x, voxel_position.y, voxel_position.z, voxel_position_local.x, voxel_position_local.y,  voxel_position_local.z);
            continue; // hasn't been unstuck
        }
        // float3 reverse_point = float3_subtract(lastUnstuck3->value, (float3) { 0, bounds3->value.y / 2.0f, 0 });
        position3->value = float3_add(lastUnstuck3->value, unstuck_push);
    }
} zoxd_system(UnstuckSystem)


/*zox_log("unstucking to [%fx%fx%f]", reverse_point.x, reverse_point.y,  reverse_point.z)
zox_log(" - voxel_position [%ix%ix%i]", voxel_position.x, voxel_position.y,  voxel_position.z)
zox_log(" - voxel_position_local [%ix%ix%i]", voxel_position_local.x, voxel_position_local.y,  voxel_position_local.z)*/
// zox_sys_e()
// zox_log("> [%s] was stuck inside voxel [%ix%ix%i:%i]", zox_get_name(e), voxel_position.x, voxel_position.y, voxel_position.z, voxel)