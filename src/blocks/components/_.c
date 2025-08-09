zox_tag(Voxel);
zox_tag(Block);
zox_tag(BlockVox);
zox_tag(BlockDungeon);
zox_tag(BlockInvinsible);
zoxc_byte(BlockModel);
zoxc_byte(BlockCollider); // zox_block_air | zox_block_solid
zoxc_byte(VoxelsDirty);
zoxc_byte(VoxBakeSide);
zoxc_byte(BlockVoxOffset);
zoxc_byte(BlockIndex);
zoxc_int3(VoxelPosition);
zoxc_byte3(VoxelLocalPosition);
zoxc_float(VoxScale);
zoxc_entity(BlockLink);
zoxc_entity(BlockPrefabLink);
zoxc_entities(VoxelLinks)

void define_components_blocks(ecs_world_t *world) {
    zox_define_tag(Voxel);
    zox_define_tag(Block);
    zox_define_tag(BlockVox);
    zox_define_tag(BlockDungeon);
    zox_define_tag(BlockInvinsible);
    zox_define_component_byte(BlockModel);
    zox_define_component_byte(BlockCollider);
    zox_define_component_byte(VoxelsDirty);
    zox_define_component_byte(VoxBakeSide);
    zox_define_component_byte(BlockVoxOffset);
    zox_define_component_byte(BlockIndex);
    zox_define_component_int3(VoxelPosition);
    zox_define_component_byte3(VoxelLocalPosition);
    zox_define_component_float(VoxScale);
    zox_define_component_entity(BlockLink);
    zox_define_component_entity(BlockPrefabLink);
    zox_define_entities_component(VoxelLinks);
}