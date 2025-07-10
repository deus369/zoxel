typedef struct {
    ecs_world_t *world;
    const float scale;
    const ChunkOctree *chunk;
    byte3 position;
    byte depth;
    const byte target_depth;
    const float3 chunk_position;
} TraverseChunk;
