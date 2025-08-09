zox_tag(Vox);
zoxc_byte(VoxType);
zoxc_byte(RubbleHeight);
zoxc_byte(GenerateVox);
zoxc_byte(CloneVox);
zoxc_byte(ChunkLod);
zoxc_int(RubbleCount);
zoxc_byte(VRegions);
zoxc_entity(CloneVoxLink);

void define_components_voxes(ecs *world) {
    zox_define_tag(Vox);
    zox_define_component_byte(VoxType);
    zox_define_component_byte(RubbleHeight);
    zox_define_component_byte(GenerateVox);
    zox_define_component_byte(ChunkLod);
    zox_define_component_byte(CloneVox);
    zox_define_component_byte(VRegions);
    zox_define_component_int(RubbleCount);
    zox_define_component_entity(CloneVoxLink);
}