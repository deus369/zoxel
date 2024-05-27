#ifndef zox_textures_core
#define zox_textures_core

#include "data/settings.c"
zox_declare_tag(Texture)
zox_declare_tag(NoiseTexture)
zox_declare_tag(IconTexture)
zox_declare_tag(FrameTexture)
zox_declare_tag(DirtTexture)
zox_declare_tag(GrassTexture)
zox_declare_tag(SandTexture)
zox_declare_tag(StoneTexture)
zox_declare_tag(ObsidianTexture)
zox_declare_tag(Tilemap)
zox_declare_tag(FillTexture)
zox_declare_tag(TextureAddNoise)
zox_component_byte(GenerateTexture)
zox_component_byte(OutlineThickness)
zox_component_byte(FrameCorner)
zox_component_double(AnimateTexture)
zox_component_int2(TextureSize)
zox_component_int2(TilemapSize)
zox_component_color(OutlineColor)
zox_component_parented(TilemapLink)
zox_entities_component(Textures)                    // this destroys linked entities (parent)
zox_memory_component(TextureData, color)
zox_memory_component(TilemapUVs, float2)
zox_memory_component(TextureLinks, ecs_entity_t)    // this links only
#include "util/textures_sdl_util.c"
#include "util/textures_util.c"
#include "util/texture_prefab_util.c"
#include "util/label_util.c"
#include "prefabs/prefabs.c"
#include "systems/animate_noise_system.c"
#include "systems/texture_update_system.c"
#include "systems/noise_texture_system.c"
#include "systems/fill_texture_system.c"
#include "systems/frame_texture_system.c"
#include "systems/tilemap_generation_system.c"
#include "tests/test_texture.c"

zox_begin_module(TexturesCore)
zox_define_tag(Texture)
zox_define_tag(NoiseTexture)
zox_define_tag(IconTexture)
zox_define_tag(FrameTexture)
zox_define_tag(DirtTexture)
zox_define_tag(GrassTexture)
zox_define_tag(SandTexture)
zox_define_tag(StoneTexture)
zox_define_tag(ObsidianTexture)
zox_define_tag(Tilemap)
zox_define_tag(FillTexture)
zox_define_tag(TextureAddNoise)
zox_define_component_byte(GenerateTexture)
zox_define_component_byte(OutlineThickness)
zox_define_component_byte(FrameCorner)
zox_define_component_int2(TextureSize)
zox_define_component_int2(TilemapSize)
zox_define_component_double(AnimateTexture)
zox_define_component_color(OutlineColor)
zox_define_component_entity(TilemapLink)
zox_define_memory_component(TextureData)
zox_define_memory_component(TilemapUVs)
zox_define_memory_component(TextureLinks)
zox_define_entities_component(Textures)
zox_filter(generate_textures2, [none] FrameTexture, [out] GenerateTexture)
zox_system(AnimateNoiseSystem, EcsOnUpdate, [out] AnimateTexture, [out] GenerateTexture)
zox_texture_system(NoiseTextureSystem, NoiseTexture, [in] Color)
zox_texture_generation_system2(FillTexture, FillTextureSystem, [in] Color)
zox_system_ctx(FrameTextureSystem, EcsPostUpdate, generate_textures2, [none] FrameTexture, [out] GenerateTexture, [in] TextureSize, [in] Color, [in] OutlineThickness, [in] FrameCorner, [out] TextureData, [out] TextureDirty)
zox_system(TilemapGenerationSystem, EcsPostUpdate, [none] Tilemap, [in] TilemapSize, [in] TextureLinks, [out] GenerateTexture, [out] TextureSize, [out] TextureData, [out] TextureDirty, [out] TilemapUVs)
// main_thread_pipeline
if (!headless) zox_system_1(TextureUpdateSystem, zox_pip_mainthread, [in] TextureData, [in] TextureSize, [in] TextureGPULink, [out] TextureDirty)
spawn_prefabs_textures_core(world);
zoxel_end_module(TexturesCore)

#endif
