zox_tag(Texture);
zox_tag(Tilemap);
// types of textures
zox_tag(NoiseTexture);
zox_tag(IconTexture);
zox_tag(FrameTexture);
zox_tag(DirtTexture);
zox_tag(GrassTexture);
zox_tag(SandTexture);
zox_tag(StoneTexture);
zox_tag(ObsidianTexture);
zox_tag(FillTexture);
zox_tag(TextureAddNoise);
zox_tag(VoxTexture);
zox_tag(TextureRGB);
zoxc_byte(GenerateTexture);
zoxc_byte(OutlineThickness);
zoxc_byte(FrameCorner);
zoxc_float(IconRadius);
zoxc_double(AnimateTexture);
zoxc_int2(TilemapSize);
zoxc_color(OutlineColor);
zoxc_entity(TilemapLink);
zoxc_entity(TextureLink);
zoxc_arrayd(TextureData, color)
zoxc_arrayd(TilemapUVs, float2)
zoxc_arrayd(TextureLinks, ecs_entity_t)
// zoxc_entities(Textures)

void define_components_textures(ecs_world_t *world) {
    zox_define_tag(Texture);
    zox_define_tag(NoiseTexture);
    zox_define_tag(IconTexture);
    zox_define_tag(FrameTexture);
    zox_define_tag(DirtTexture);
    zox_define_tag(GrassTexture);
    zox_define_tag(SandTexture);
    zox_define_tag(StoneTexture);
    zox_define_tag(ObsidianTexture);
    zox_define_tag(Tilemap);
    zox_define_tag(FillTexture);
    zox_define_tag(TextureAddNoise);
    zox_define_tag(VoxTexture);
    zox_define_tag(TextureRGB);
    zox_define_component_byte(GenerateTexture);
    zox_define_component_byte(OutlineThickness);
    zox_define_component_byte(FrameCorner);
    zox_define_component_float(IconRadius);
    zox_define_component_int2(TilemapSize);
    zox_define_component_double(AnimateTexture);
    zox_define_component_color(OutlineColor);
    zox_define_component_entity(TilemapLink);
    zox_define_component_entity(TextureLink);
    zox_define_memory_component(TextureData);
    zox_define_memory_component(TilemapUVs);
    zox_define_memory_component(TextureLinks);
    // zox_define_entities_component(Textures);
}