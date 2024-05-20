// spawning block vox entities during generation step!
// ChunkDirty process or nah?
void BlockVoxSpawnSystem(ecs_iter_t *it) {
    zox_iter_world()
    zox_field_in(ChunkOctree, chunkOctrees, 1)
    zox_field_in(VoxLink, voxLinks, 2)
    zox_field_out(Children, childrens, 3)
    for (int i = 0; i < it->count; i++) {
        zox_field_i_in(VoxLink, voxLinks, voxLink)
        if (!voxLink->value) continue;
        zox_field_i_in(ChunkOctree, chunkOctrees, chunkOctree)
        zox_field_i_out(Children, childrens, children)
        // spawn the things as children to terrain Chunks!
        // first initt our vox types array here so i can use that in node checks
        // next find blocks of vox type in nodes, and call a spawn_voxel_in_world function!
    }
} zox_declare_system(BlockVoxSpawnSystem)
