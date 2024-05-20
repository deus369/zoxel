#ifndef zox_voxels_blocks
#define zox_voxels_blocks

// todo: implement BlockCollider in physics
#include "data/model_types.c"
#include "data/block_types.c"
#include "data/spawn_voxel.c"
zox_declare_tag(Voxel)
zox_declare_tag(BlockVox)
zox_component_byte(BlockModel)
zox_component_byte(BlockCollider) // zox_block_air | zox_block_solid
zox_component_int3(VoxelPosition)
zox_component_float(VoxScale)
zox_entities_component(VoxelLinks)
#include "util/generation_util.c"
#include "prefabs/prefabs.c"

zox_begin_module(Blocks)
zox_define_tag(Voxel)
zox_define_tag(BlockVox)
zox_define_component_byte(BlockModel)
zox_define_component_byte(BlockCollider)
zox_define_component_int3(VoxelPosition)
zox_define_component_float(VoxScale)
zox_define_entities_component(VoxelLinks)
zoxel_end_module(Blocks)

#endif
