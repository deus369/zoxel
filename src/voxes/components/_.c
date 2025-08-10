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
    zoxd_byte(VoxType);
    zoxd_byte(RubbleHeight);
    zoxd_byte(GenerateVox);
    zoxd_byte(ChunkLod);
    zoxd_byte(CloneVox);
    zoxd_byte(VRegions);
    zox_define_component_int(RubbleCount);
    zox_define_component_entity(CloneVoxLink);
}