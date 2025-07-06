// if character falls through map, push up
// todo: draw lines on this to test why it suddenly detects..!
void VoxelUnstuckSystem(ecs_iter_t *it) {
    const byte depth = terrain_depth;
    const int3 chunk_dimensions = int3_single(powers_of_two[depth]);
    const float unstuck_push = 1.0f;
    zox_field_world()
    zox_field_in(VoxLink, voxLinks, 1)
    // zox_field_in(ChunkLink, chunkLinks, 2)
    // zox_field_in(ChunkPosition, chunkPositions, 3)
    // zox_field_in(Bounds3D, bounds3Ds, 4)
    zox_field_out(Position3D, position3Ds, 5)
    // find realm first
    const VoxelLinks *voxels = get_first_terrain_voxels(world, voxLinks, it->count);
    if (!voxels) {
        return;
    }
    byte block_collisions[voxels->length + 1];
    get_block_collisions(world, voxels, block_collisions);
    for (int i = 0; i < it->count; i++) {
        zox_field_i(VoxLink, voxLinks, voxLink)
        // zox_field_i(Bounds3D, bounds3Ds, bounds3D)
        // zox_field_i(ChunkLink, chunkLinks, chunkLink)
        // zox_field_i(ChunkPosition, chunkPositions, chunkPosition)
        zox_field_o(Position3D, position3Ds, position3D)

        zox_geter(voxLink->value, ChunkLinks, chunkLinks)
        const int3 chunk_position = real_position_to_chunk_position(position3D->value, chunk_dimensions, depth);
        const ecs_entity_t chunk = int3_hashmap_get(chunkLinks->value, chunk_position);

        if (!zox_valid(chunk)) {
            continue;
        }
        if (!zox_has(chunk, ChunkOctree)) {
            zox_log_error("chunk [%s:%lu] doesn't have a ChunkOctree!", zox_get_name(chunk), chunk)
            continue;
        }
        zox_geter(chunk, ChunkOctree, node)
        // const int3 chunk_dimensions = int3_single(powers_of_two[node->linked]);
        const byte3 chunk_dimensions_b3 = int3_to_byte3(chunk_dimensions);
        // positions
        const int3 voxel_position = real_position_to_voxel_position(position3D->value, node->linked);
        byte3 voxel_position_local = get_local_position_byte3(voxel_position, chunk_position, chunk_dimensions_b3);
        // voxel
        const byte voxel = get_octree_voxel(node, &voxel_position_local, node->linked);
        if (voxel >= voxels->length) {
            zox_log_error("voxel [%i] out of range [0-%i]", voxel, voxels->length)
            break;
        }
        if (voxel && block_collisions[voxel]) {
            position3D->value.y += unstuck_push;
            zox_field_e()
            // zox_log("> [%s] was stuck inside voxel [%ix%ix%i:%i]", zox_get_name(e), voxel_position.x, voxel_position.y, voxel_position.z, voxel)
        }
    }
} zox_declare_system(VoxelUnstuckSystem)