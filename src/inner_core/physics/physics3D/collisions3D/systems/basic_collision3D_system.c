
// todo seperate voxel position, and chunk position updates outside of this
// todo check normal of voxel position difference, base bounce velocity off that instead of just y axis
void BasicCollision3DSystem(ecs_iter_t *it) {
    #ifdef zoxel_disable_velocity
        return;
    #endif
    double delta_time = zoxel_delta_time;
    const ChunkLink *chunkLinks = ecs_field(it, ChunkLink, 1);
    const ChunkPosition *chunkPositions = ecs_field(it, ChunkPosition, 2);
    Position3D *position3Ds = ecs_field(it, Position3D, 3);
    Velocity3D *velocity3Ds = ecs_field(it, Velocity3D, 4);
    VoxelPosition *voxelPositions = ecs_field(it, VoxelPosition, 5);
    for (int i = 0; i < it->count; i++) {
        const ChunkPosition *chunkPosition = &chunkPositions[i];
        Position3D *position3D = &position3Ds[i];
        VoxelPosition *voxelPosition = &voxelPositions[i];
        int3 global_voxel_position = get_voxel_position(position3D->value);
        int3 new_position = get_local_position(global_voxel_position, chunkPosition->value, default_chunk_size);
        if (!int3_equals(new_position, voxelPosition->value)) {
            int3 old_voxel_position = voxelPosition->value;
            voxelPosition->value = new_position;
            #ifdef zoxel_debug_basic_collision3D_system
                zoxel_log(" > chunk_position [%ix%ix%i]\n", chunkPosition->value.x, chunkPosition->value.y, chunkPosition->value.z);
                zoxel_log("     + voxel position updated [%ix%ix%i]\n", new_position.x, new_position.y, new_position.z);
                zoxel_log("     + real position was [%fx%fx%f]\n", position3D->value.x, position3D->value.y, position3D->value.z);
            #endif
            const ChunkLink *chunkLink = &chunkLinks[i];
            if (chunkLink->value != 0) {
                // get voxel from new position
                const ChunkOctree *chunkOctree = ecs_get(world, chunkLink->value, ChunkOctree);
                if (chunkOctree != NULL) {
                    byte3 voxel_position_2 = (byte3) { voxelPosition->value.x, voxelPosition->value.y, voxelPosition->value.z };
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
                            Velocity3D *velocity3D = &velocity3Ds[i];
                            position3D->value.x -= velocity3D->value.x * delta_time * bounce_multiplier;
                            position3D->value.y -= velocity3D->value.y * delta_time * bounce_multiplier;
                            position3D->value.z -= velocity3D->value.z * delta_time * bounce_multiplier;
                            // get normal of collision here
                            if (old_voxel_position.x != voxelPosition->value.x) {
                                velocity3D->value.x *= -bounce_lost_force;
                            }
                            if (old_voxel_position.y != voxelPosition->value.y) {
                                velocity3D->value.y *= -bounce_lost_force;
                            }
                            if (old_voxel_position.z != voxelPosition->value.z) {
                                velocity3D->value.z *= -bounce_lost_force;
                            }
                            // velocity3D->value.y = 0;
                            // float3_subtract_float3_p(&position3D->value, velocity3D->value);
                            if (position3D->value.y < -256) {
                                // zoxel_log(" !!! npc is too far deep %lu\n", it->entities[i]);
                                ecs_delete(world, it->entities[i]);
                            }
                        }
                    }
                }
            }
            #ifdef zoxel_debug_basic_collision3D_system
                else {
                    zoxel_log(" > vox has no chunk linked [%lu]\n", it->entities[i]);
                }
            #endif
        }
    }
}
zoxel_declare_system(BasicCollision3DSystem)