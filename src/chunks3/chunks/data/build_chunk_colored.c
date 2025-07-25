typedef struct {
    // chunk
    const VoxelNode *chunk_octree;
    // vox
    const ColorRGBs *colorRGBs;
    const byte chunk_depth;    // our lod
    const float vox_scale;
    const float3 total_mesh_offset;
    // neighbors
    const VoxelNode **neighbors; // array of pointers
    const byte *neighbor_lods; // array
    // chunk output
    MeshIndicies *meshIndicies;
    MeshVertices *meshVertices;
    MeshColorRGBs *meshColorRGBs;
} BuildChunkColored;