// todo seperate voxel position, and chunk position updates outside of this
// todo check normal of voxel position difference, base bounce velocity off that instead of just y axis
void BasicCollision3DSystem(ecs_iter_t *it) {
    double deltaTime = (double) it->delta_time;
    const int3 chunk_size = (int3) { 16, 16, 16 };
    const ChunkLink *chunkLinks = ecs_field(it, ChunkLink, 1);
    const ChunkPosition *chunkPositions = ecs_field(it, ChunkPosition, 2);
    Position3D *position3Ds = ecs_field(it, Position3D, 3);
    Velocity3D *velocity3Ds = ecs_field(it, Velocity3D, 4);
    VoxelPosition *voxelPositions = ecs_field(it, VoxelPosition, 5);
    for (int i = 0; i < it->count; i++) {
        // get voxel_position
        // has voxel_position changed? if it has, get voxel type based on position
        Position3D *position3D = &position3Ds[i];
        VoxelPosition *voxelPosition = &voxelPositions[i];
        const ChunkPosition *chunkPosition = &chunkPositions[i];
        // int3 chunk_position = get_chunk_position(position3D->value, chunk_size);
        int3 global_voxel_position = get_voxel_position(position3D->value);
        int3 new_position = get_local_position(global_voxel_position, chunkPosition->value, chunk_size);
        // zoxel_log(" > chunk_position [%ix%ix%i]\n", chunk_position.x, chunk_position.y, chunk_position.z);
        // zoxel_log(" > new_position [%ix%ix%i]\n", new_position.x, new_position.y, new_position.z);
        if (!int3_equals(new_position, voxelPosition->value)) {
            voxelPosition->value = new_position;
            // zoxel_log("     + voxel position updated [%ix%ix%i]\n", new_position.x, new_position.y, new_position.z);
            const ChunkLink *chunkLink = &chunkLinks[i];
            if (chunkLink->value != 0) {
                // get voxel from new position
                const ChunkOctree *chunkOctree = ecs_get(world, chunkLink->value, ChunkOctree);
                if (chunkOctree != NULL) {
                    unsigned char voxel = get_octree_voxel(chunkOctree, voxelPosition->value, max_octree_depth);
                    // zoxel_log(" > voxel %i\n", voxel);
                    // if voxel is solid, reset positin to last position, by subtracting velocity
                    if (voxel != 0 && voxel != 255) {
                        // zoxel_log(" > voxel collided %i\n", voxel);
                        Velocity3D *velocity3D = &velocity3Ds[i];
                        position3D->value.x -= velocity3D->value.x * deltaTime * bounce_multiplier;
                        position3D->value.y -= velocity3D->value.y * deltaTime * bounce_multiplier;
                        position3D->value.z -= velocity3D->value.z * deltaTime * bounce_multiplier;
                        velocity3D->value.y *= -1.0f * bounce_lost_force;
                        // float3_subtract_float3_p(&position3D->value, velocity3D->value);
                    }
                }
            }
        }
    }
}
zoxel_declare_system(BasicCollision3DSystem)


// const ChunkLinks *chunkLinks = ecs_get(world, main_terrain_world, ChunkLinks);
// chunk_entity = int3_hash_map_get(chunkLinks->value, chunk_position);
// zoxel_log(" > terrain chunks %i\n", chunkLinks->length);
/*for (int j = 0; j < chunkLinks->length; j++) {
    const ChunkPosition *chunkPosition = ecs_get(world, chunkLinks->value[j], ChunkPosition);
    if (int3_equals(chunkPosition->value, chunk_position)) { // int3_zero)) {
        chunk_entity = chunkLinks->value[j];
        // zoxel_log("     + found zero chunk at %i\n", j);
        break;
    }
}*/