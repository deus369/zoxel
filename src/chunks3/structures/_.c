#ifndef zox_voxels_structures
#define zox_voxels_structures

// todo: make basic building 12x6x6, spawn randomly in chunks
// todo: remember dont spawn chunk if surrounding chunk hasn't spawn their structures yet
//          - since structures will update voxels accross chunks
// todo: debug system will render bounds of structures around map (based on LODs)
// todo: spawn tree structures out of grass voxels, the structure bounding boxes exist to limit their growths

zox_tag(VoxStructure);

void spawn_prefabs_structures(ecs *world) {
    (void) world;
}

zox_begin_module(Structures)
    zox_define_tag(VoxStructure);
    add_hook_spawn_prefabs(spawn_prefabs_structures);
zox_end_module(Structures)

#endif
