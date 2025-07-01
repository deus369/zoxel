typedef struct {
    // chunk
    const ChunkOctree *chunk_octree;
    // vox
    const ColorRGBs *colorRGBs;
    const byte chunk_depth;    // our lod
    const float vox_scale;
    const float3 total_mesh_offset;
    // neighbors
    const ChunkOctree **neighbors; // array of pointers
    const byte *neighbor_lods; // array
    // chunk output
    MeshIndicies *meshIndicies;
    MeshVertices *meshVertices;
    MeshColorRGBs *meshColorRGBs;
} BuildChunkColored;