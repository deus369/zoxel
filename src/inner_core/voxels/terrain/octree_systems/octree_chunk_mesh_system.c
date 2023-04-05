// only update mesh when none of neighbors are dirty
void OctreeChunkMeshSystem(ecs_iter_t *it) {
    ChunkDirtier *chunkDirtiers = ecs_field(it, ChunkDirtier, 1);
    const ChunkNeighbors *chunkNeighbors = ecs_field(it, ChunkNeighbors, 2);
    MeshDirty *meshDirtys = ecs_field(it, MeshDirty, 3);
    for (int i = 0; i < it->count; i++) {
        ChunkDirtier *chunkDirtier = &chunkDirtiers[i];
        if (chunkDirtier->value == 1) {
            /*const ChunkNeighbors *chunkNeighbors2 = &chunkNeighbors[i];
            const unsigned char dirty_left = chunkNeighbors2->value[0] == 0 ?
                0 : ecs_get(it->world, chunkNeighbors2->value[0], ChunkDirty)->value;
            const unsigned char dirty_right = chunkNeighbors2->value[1] == 0 ?
                0 : ecs_get(it->world, chunkNeighbors2->value[1], ChunkDirty)->value;
            const unsigned char dirty_down = chunkNeighbors2->value[2] == 0 ?
                0 : ecs_get(it->world, chunkNeighbors2->value[2], ChunkDirty)->value;
            const unsigned char dirty_up = chunkNeighbors2->value[3] == 0 ?
                0 : ecs_get(it->world, chunkNeighbors2->value[3], ChunkDirty)->value;
            const unsigned char dirty_back = chunkNeighbors2->value[4] == 0 ?
                0 : ecs_get(it->world, chunkNeighbors2->value[4], ChunkDirty)->value;
            const unsigned char dirty_front = chunkNeighbors2->value[5] == 0 ?
                0 : ecs_get(it->world, chunkNeighbors2->value[5], ChunkDirty)->value;*/
            //if (dirty_left == 0 && dirty_left == 0 && dirty_down == 0 && dirty_up == 0 && dirty_back == 0 && dirty_front == 0) {
                MeshDirty *meshDirty = &meshDirtys[i];
                chunkDirtier->value = 0;
                meshDirty->value = 1;
            //}
        }
    }
}
zoxel_declare_system(OctreeChunkMeshSystem)