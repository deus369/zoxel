#ifndef zox_voxels_blocks
#define zox_voxels_blocks

// todo: implement BlockCollider in physics
#include "data/model_types.c"
#include "data/block_types.c"
#include "data/block_sides.c"
#include "data/spawn_block.c"
zox_declare_tag(Voxel)
zox_declare_tag(Block)
zox_declare_tag(BlockVox)
zox_declare_tag(BlockDungeon)
zox_component_byte(BlockModel)
zox_component_byte(BlockCollider) // zox_block_air | zox_block_solid
zox_component_byte(VoxelsDirty)
zox_component_byte(VoxBakeSide)
zox_component_byte(BlockVoxOffset)
zox_component_byte(BlockIndex)
zox_component_int3(VoxelPosition)
zox_component_float(VoxScale)
zox_component_entity(ModelLink)
zox_entities_component(VoxelLinks)
zox_component_entity(BlockLink)
zox_component_entity(BlockPrefabLink)
#include "util/generation_util.c"
#include "prefabs/prefabs.c"

zox_begin_module(Blocks)
zox_define_tag(Voxel)
zox_define_tag(Block)
zox_define_tag(BlockVox)
zox_define_tag(BlockDungeon)
zox_define_component_byte(BlockModel)
zox_define_component_byte(BlockCollider)
zox_define_component_byte(VoxelsDirty)
zox_define_component_byte(VoxBakeSide)
zox_define_component_byte(BlockVoxOffset)
zox_define_component_byte(BlockIndex)
zox_define_component_int3(VoxelPosition)
zox_define_component_float(VoxScale)
zox_define_component_entity(ModelLink)
zox_define_entities_component(VoxelLinks)
zox_define_component_entity(BlockLink)
zox_define_component_entity(BlockPrefabLink)
spawn_prefabs_blocks(world);
zoxel_end_module(Blocks)

#endif
