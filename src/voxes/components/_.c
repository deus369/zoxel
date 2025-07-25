zox_declare_tag(Vox)
zox_component_byte(VoxType)
zox_component_byte(RubbleHeight)
zox_component_byte(GenerateVox)
zox_component_byte(CloneVox)
zox_component_byte(ChunkLod)
zox_component_int(RubbleCount)
zox_component_entity(CloneVoxLink)

void define_components_voxes(ecs_world_t *world) {
    zox_define_tag(Vox)
    zox_define_component_byte(VoxType)
    zox_define_component_byte(RubbleHeight)
    zox_define_component_byte(GenerateVox)
    zox_define_component_byte(ChunkLod)
    zox_define_component_byte(CloneVox)
    zox_define_component_int(RubbleCount)
    zox_define_component_entity(CloneVoxLink)
}