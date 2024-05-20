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
        zox_field_i_in(Position3D, position3Ds, position3D)
        zox_field_i_out(Children, childrens, children)
        // spawn the things as children to terrain Chunks!
    }
} zox_declare_system(BlockVoxSpawnSystem)
