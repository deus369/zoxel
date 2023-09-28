#ifndef zoxel_textures_core
#define zoxel_textures_core

// zoxel_settings
#include "settings/settings.c"
// zoxel_component_includes
zox_declare_tag(Texture)
zox_declare_tag(NoiseTexture)
zox_declare_tag(FrameTexture)
zox_declare_tag(DirtTexture)
zox_declare_tag(GrassTexture)
zox_declare_tag(SandTexture)
zox_declare_tag(StoneTexture)
zox_declare_tag(ObsidianTexture)
zox_declare_tag(Tilemap)
zox_declare_tag(FillTexture)
zox_entity_parent_component(TilemapLink)
zox_memory_component(TextureData, color)
zox_component(TextureSize, int2)
zox_component(TilemapSize, int2)
zox_byte_component(GenerateTexture) 
zox_component(AnimateTexture, double)
zox_entities_component(Textures)                    // this destroys linked entities (parent)
zox_memory_component(TextureLinks, ecs_entity_t)    // this links only
zox_memory_component(TilemapUVs, float2)
zox_byte_component(OutlineThickness)
zox_byte_component(FrameCorner)
// zoxel_util_includes
#include "util/textures_sdl_util.c"
#include "util/textures_util.c"
// zoxel_prefab_includes
#include "prefabs/noise_texture.c"
#include "prefabs/dirt_texture.c"
#include "prefabs/tilemap.c"
// zoxel_system_includes
#include "systems/animate_noise_system.c"
#include "systems/texture_update_system.c"
#include "systems/noise_texture_system.c"
#include "systems/fill_texture_system.c"
#include "systems/frame_texture_system.c"
#include "systems/tilemap_generation_system.c"
#include "tests/test_texture.c"

void spawn_prefabs_textures_core(ecs_world_t *world) {
    spawn_prefab_noise_texture(world);
    spawn_prefab_texture_dirt(world);
    spawn_prefab_tilemap(world);
}

zox_begin_module(TexturesCore)
// zoxel_component_defines
zox_define_tag(Texture)
zox_define_tag(NoiseTexture)
zox_define_tag(FrameTexture)
zox_define_tag(DirtTexture)
zox_define_tag(GrassTexture)
zox_define_tag(SandTexture)
zox_define_tag(StoneTexture)
zox_define_tag(ObsidianTexture)
zox_define_tag(Tilemap)
zox_define_tag(FillTexture)
zox_define_entity_parent_component(TilemapLink)
zox_define_component(TextureSize)
zox_define_component(GenerateTexture)
zox_define_component(AnimateTexture)
zox_define_component(TilemapSize)
zox_define_component(OutlineThickness)
zox_define_component(FrameCorner)
zox_define_memory_component(TextureData)
zox_define_memory_component(TilemapUVs)
zox_define_entities_component(Textures)
zox_define_memory_component(TextureLinks)
// zoxel_filter_defines
zox_filter(generate_textures2, [none] FrameTexture, [out] GenerateTexture)
// zoxel_system_defines
zox_system(AnimateNoiseSystem, EcsOnUpdate, [out] AnimateTexture, [out] GenerateTexture)
zox_texture_generation_system(NoiseTexture, NoiseTextureSystem)
zox_texture_generation_system2(FillTexture, FillTextureSystem, [in] Color)
zox_system_ctx(FrameTextureSystem, EcsPostUpdate, generate_textures2, [none] FrameTexture, [out] GenerateTexture, [in] TextureSize, [in] Color, [in] OutlineThickness, [in] FrameCorner, [out] TextureData, [out] TextureDirty)
zox_system(TilemapGenerationSystem, EcsPostUpdate, [none] Tilemap, [in] TilemapSize, [in] TextureLinks, [out] GenerateTexture, [out] TextureSize, [out] TextureData, [out] TextureDirty, [out] TilemapUVs)
zox_system_1(TextureUpdateSystem, main_thread_pipeline, [out] TextureDirty, [in] TextureData, [in] TextureSize, [in] TextureGPULink)
zoxel_end_module(TexturesCore)

#endif