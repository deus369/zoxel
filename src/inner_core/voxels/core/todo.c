//! The voxels core Sub Module.
/**
*   Rendering
*   \todo Only push voxel data to the GPU
*   \todo First use a Point Render system to render voxel data
*   \todo Try out voxel raycasting method for better lighting
*
*   Octree Implementation
*   \todo Spawn an Oct Node of 1 Voxel, if open, create 8 sub chunk nodes
*   \todo Create prefab for terrain chunk with octree
*   \todo Generate terrain if ChunkOctree
*   \todo Debug system that shows chunks octree nodes
*   \todo Create mesh if ChunkOctree
*   \todo Render chunks at a set resolution
*
*   Resolutions:
*   \todo Create a state component for chunks division level (resolution)
*   \todo Debug system for division, lines through chunks
*   \todo Render chunks further away with lower max resolution
*
*   Culling:
*   \todo Cull faces?
*   \todo Greedy meshes for voxes
*   \todo Camera view matrix cull chunks by enabling/disabling render flag
*
*   Streaming:
*   \todo When camera moves to a new chunk, update the stream point
*   \todo For all cameras, load/unload chunks when stream points update
*   \todo Test this with local coop cameras
*
*   More
*   \todo Update chunk system? test updates on them, including closing and opening of nodes
*   \todo Load Vox models as an octree (nearest division of 2 size)
*   \todo Load characters in each chunk, set their resolution based on chunk resolution
*   \todo A debugger ui that shows all stats, in a toggleable window:
*          -> terrain chunks [40960] characters [4200] minivoxes [12030] particles [20041] particle systems [2031]
*   \todo Instance vox models when using the same ones, instead of generating each time.
*       -> We can still have mutants but this will greatly improve performance.
*/