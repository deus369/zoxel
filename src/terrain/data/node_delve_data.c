typedef struct {
    ChunkOctree *chunk; // const
    int3 octree_position;
    byte depth;
    const byte max_depth;
} NodeDelveData;