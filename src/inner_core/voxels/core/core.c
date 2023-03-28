#ifndef zoxel_voxels_core
#define zoxel_voxels_core

#define overall_voxel_scale 32.0f // 64.0f; // 4.0f // 2.0f;
const int chunk_length = 16;
const int3 chunk_size = { chunk_length, chunk_length, chunk_length };
const double noiseChunkAnimateSpeed = 0.5; // 1 / 8.0;
const int dissapearChance = 92;
const float spawnRange = 0.96f;
zoxel_declare_tag(Chunk)
zoxel_declare_tag(NoiseChunk)
zoxel_component(ChunkSize, int3)                        //! A simple chunk with an array of voxels.
zoxel_component(ChunkPosition, int3)                    //! A local position of a chunk inside a Vox.
zoxel_component(AnimateChunk, double)                   //! A state for animating textures.
zoxel_component(VoxLink, ecs_entity_t)                  //! A link to a vox.
zoxel_byte_component(GenerateChunk)                     //! A state for generating chunks.
zoxel_byte_component(ChunkDirty)                        //! A state for generating chunk meshes.
zoxel_memory_component(ChunkData, unsigned char)        //! A simple chunk with an array of voxels.
zoxel_memory_component(ChunkLinks, ecs_entity_t)        //! A list to all chunks in a Vox model.
zoxel_memory_component(ChunkNeighbors, ecs_entity_t)    //! A list to all chunks in a Vox model.
zoxel_octree_component(ChunkOctree, unsigned char, 0)   //! A chunk that stores voxels in an octree.
zoxel_byte_component(ChunkDivision)                     //! The resolution of each chunk, distance to nearest camera.
#include "util/voxel_mesh_util.c"
#include "util/chunk.c"
#include "util/chunk_build_util.c"
#include "util/voxel_util.c"
#include "prefabs/chunk.c"
#include "prefabs/voxel_chunk_mesh.c"
#include "prefabs/noise_chunk.c"
#include "systems/noise_chunk_system.c"
#include "systems/animate_chunk_system.c"
#include "systems/chunk_build_system.c"
#include "systems/chunk_colors_build_system.c"
// \todo for things like this, declare system in component declaration - a variable that resets~
zoxel_reset_system(GenerateChunkResetSystem, GenerateChunk)
zoxel_reset_system(ChunkDirtyResetSystem, ChunkDirty)

void define_voxels_core_components(ecs_world_t *world) {
    zoxel_define_tag(Chunk)
    zoxel_define_component(ChunkDirty)
    zoxel_define_component(ChunkSize)
    zoxel_define_component(GenerateChunk)
    zoxel_define_component(ChunkPosition)
    zoxel_define_component(ChunkDivision)
    zoxel_define_component(VoxLink)
    zoxel_define_memory_component(ChunkData)
    zoxel_define_memory_component(ChunkLinks)
    zoxel_define_memory_component(ChunkNeighbors)
    zoxel_octree_component_define(ChunkOctree)
    // extras - move to another module
    zoxel_define_tag(NoiseChunk)
    zoxel_define_component(AnimateChunk)
}

void define_voxels_core_systems(ecs_world_t *world) {
    zoxel_reset_system_define(GenerateChunkResetSystem, GenerateChunk)
    zoxel_reset_system_define(ChunkDirtyResetSystem, ChunkDirty)
    if (!headless) {
        zoxel_filter(generateChunkQuery, world, [in] GenerateChunk)
        zoxel_system_ctx(world, ChunkBuildSystem, EcsOnUpdate, generateChunkQuery,
            [in] ChunkDirty, [in] ChunkData, [in] ChunkSize,
            [out] MeshIndicies, [out] MeshVertices, [out] MeshDirty,
            [none] !MeshUVs, [none] !MeshColors)
        zoxel_system_ctx(world, ChunkColorsBuildSystem, EcsOnUpdate, generateChunkQuery,
            [in] ChunkDirty, [in] ChunkData, [in] ChunkSize, [in] Colors,
            [out] MeshIndicies, [out] MeshVertices, [out] MeshColors, [out] MeshDirty,
            [none] !MeshUVs)
    }
    zoxel_system_main_thread(world, AnimateChunkSystem, EcsOnLoad, [out] AnimateChunk, [out] GenerateChunk)
    zoxel_filter(generateNoiseChunkQuery, world, [none] NoiseChunk, [in] GenerateChunk)
    zoxel_system_ctx(world, NoiseChunkSystem, EcsPostLoad, generateNoiseChunkQuery,
        [none] NoiseChunk, [out] ChunkDirty, [out] ChunkData, [in] ChunkSize, [in] GenerateChunk)
}

void VoxelsCoreImport(ecs_world_t *world) {
    zoxel_module(VoxelsCore)
    define_voxels_core_components(world);
    define_voxels_core_systems(world);
    spawn_voxel_chunk_mesh_prefab(world);
    spawn_prefab_noise_chunk(world);
    #ifdef zoxel_test_voxels
    spawn_voxel_noise_chunk_mesh(world, prefab_noise_chunk, (float3) { 0, 0, 0 }, 0.15f);
    spawn_voxel_noise_chunk_mesh(world, prefab_noise_chunk, (float3) { 0, -spawnRange, 0 }, 0.05f);
    spawn_voxel_noise_chunk_mesh(world, prefab_noise_chunk, (float3) { 0, spawnRange, 0 }, 0.05f);
    spawn_voxel_noise_chunk_mesh(world, prefab_noise_chunk, (float3) { -spawnRange, 0, 0 }, 0.05f);
    spawn_voxel_noise_chunk_mesh(world, prefab_noise_chunk, (float3) { spawnRange, 0, 0 }, 0.05f);
    #endif
}
#endif