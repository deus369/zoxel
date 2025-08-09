#include "build_chunk.c"
#include "render.c"
#include "flatlands.c"
#include "grasslands.c"
#include "realm.c"
#include "chunk_bounds_debug_system.c"
zox_declare_system_state_event(RealmBlocks, GenerateRealm, zox_generate_realm_blocks, spawn_realm_blocks)
zox_declare_system_state_event(RealmTilemaps, GenerateRealm, zox_generate_realm_tilemaps, spawn_realm_tilemaps)

// Note: Updates on VoxelNode has to be done in PostLoad, away from use of Voxels, due to the cleaning step
void define_systems_terrain(ecs_world_t *world) {
    zox_define_system_state_event_1(RealmBlocks, EcsOnLoad, realms.GenerateRealm, [none] realms.Realm)
    zox_define_system_state_event_1(RealmTilemaps, EcsOnLoad, realms.GenerateRealm, [none] realms.Realm)
    // generate terrain
    zox_system(ChunkFlatlandSystem, zoxp_voxels_write,
            [in] chunks3.ChunkPosition,
            [out] chunks3.GenerateChunk,
            [out] chunks3.VoxelNode,
            [out] chunks3.NodeDepth,
            [none] TerrainChunk,
            [none] FlatlandChunk)
    zox_system(GrassyPlainsSystem, zoxp_voxels_write,
            [in] chunks3.ChunkPosition,
            [in] rendering.RenderLod,
            [in] rendering.RenderDistanceDirty,
            [in] chunks3.VoxelNodeLoaded,
            [in] chunks3.VoxLink,
            [out] chunks3.VoxelNode,
            [out] chunks3.NodeDepth,
            [out] chunks3.VoxelNodeDirty,
            [none] !FlatlandChunk,
            [none] TerrainChunk)
    if (!headless) {
        // move this into chunk3, for chunk3_textured
        zox_system(Chunk3BuildSystem, zoxp_voxels_read,
                [in] chunks3.ChunkMeshDirty,
                [in] chunks3.VoxLink,
                [in] chunks3.VoxelNode,
                [in] chunks3.NodeDepth,
                [in] rendering.RenderLod,
                [in] chunks3.ChunkNeighbors,
                [in] blocks.VoxScale,
                [out] rendering.MeshIndicies,
                [out] rendering.MeshVertices,
                [out] rendering.MeshUVs,
                [out] rendering.MeshColorRGBs,
                [out] rendering.MeshDirty,
                [none] chunks3.ChunkTextured)
        // move this into chunk3, for chunk3_textured
        zox_render3D_system(Chunk3RenderSystem,
                [in] transforms3.TransformMatrix,
                [in] rendering.MeshGPULink,
                [in] rendering.UvsGPULink,
                [in] rendering.ColorsGPULink,
                [in] rendering.MeshIndicies,
                [in] chunks3.VoxLink,
                [in] rendering.RenderDisabled) // builds meshes
    }
#ifdef zox_debug_chunk_bounds
    zox_system_1(ChunkBoundsDrawSystem, zoxp_mainthread,
            [in] transforms3.Position3D,
            [in] chunks3.ChunkSize,
            [in] blocks.VoxScale,
            [in] rendering.RenderDisabled,
            [none] TerrainChunk)
#endif
}