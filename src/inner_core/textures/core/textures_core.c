#ifndef zox_mod_textures_core
#define zox_mod_textures_core

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
zox_declare_tag(VoxTexture)
zox_declare_tag(TextureRGB)
zox_component_byte(GenerateTexture)
zox_component_byte(OutlineThickness)
zox_component_byte(FrameCorner)
zox_component_float(IconRadius)
zox_component_double(AnimateTexture)
zox_component_int2(TextureSize)
zox_component_int2(TilemapSize)
zox_component_color(OutlineColor)
zox_component_entity(TilemapLink)
zox_component_entity(TextureLink)
zox_entities_component(Textures)                    // this destroys linked entities (parent)
zox_memory_component(TextureData, color)
zox_memory_component(TilemapUVs, float2)
zox_memory_component(TextureLinks, ecs_entity_t)    // this links only
#include "data/settings.c"
#include "data/generate_texture_states.c"
#include "util/textures_sdl_util.c"
#include "util/textures_util.c"
#include "util/voronoi2D.c"
#include "util/texture_prefab_util.c"
#include "util/label_util.c"
#include "prefabs/prefabs.c"
#include "systems/animate_noise_system.c"
#include "systems/texture_update_system.c"
#include "systems/noise_texture_system.c"
#include "systems/fill_texture_system.c"
#include "systems/frame_texture_system.c"
#include "systems/tilemap_generation_system.c"
#include "systems/mouse_texture_system.c"
#include "tests/test_texture.c"
zox_increment_system_with_reset(GenerateTexture, zox_generate_texture_end)

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
zox_define_tag(VoxTexture)
zox_define_tag(TextureRGB)
zox_define_component_byte(GenerateTexture)
zox_define_component_byte(OutlineThickness)
zox_define_component_byte(FrameCorner)
zox_define_component_float(IconRadius)
zox_define_component_int2(TextureSize)
zox_define_component_int2(TilemapSize)
zox_define_component_double(AnimateTexture)
zox_define_component_color(OutlineColor)
zox_define_component_entity(TilemapLink)
zox_define_component_entity(TextureLink)
zox_define_memory_component(TextureData)
zox_define_memory_component(TilemapUVs)
zox_define_memory_component(TextureLinks)
zox_define_entities_component(Textures)
zox_filter(generate_textures2, [none] FrameTexture, [out] GenerateTexture)
zox_system(AnimateNoiseSystem, zox_pip_texture_generation, [out] AnimateTexture, [out] GenerateTexture)
zox_texture_system(NoiseTextureSystem, NoiseTexture, [in] Color)
zox_texture_generation_system2(FillTexture, FillTextureSystem, [in] Color)
zox_system_ctx(FrameTextureSystem, zox_pip_texture_generation, generate_textures2, [none] FrameTexture, [out] GenerateTexture, [in] TextureSize, [in] Color, [in] OutlineThickness, [in] FrameCorner, [out] TextureData, [out] TextureDirty)
zox_system(TilemapGenerationSystem, zox_pip_texture_generation, [in] TilemapSize, [in] TextureLinks, [out] GenerateTexture, [out] TextureSize, [out] TextureData, [out] TextureDirty, [out] TilemapUVs, [none] Tilemap)
if (!headless) zox_system_1(TextureUpdateSystem, zox_pip_mainthread, [in] TextureData, [in] TextureSize, [in] TextureGPULink, [out] TextureDirty)
zox_define_increment_system(GenerateTexture, EcsOnLoad, [none] Texture)
zox_system(MouseTextureSystem, EcsOnUpdate, [in] MouseLock, [in] TextureLink)
spawn_prefabs_textures_core(world);
zoxel_end_module(TexturesCore)

#endif
