#ifndef zoxel_textures_core
#define zoxel_textures_core

#include "settings/settings.c"
// zoxel_component_includes
zox_declare_tag(Texture)
zox_declare_tag(NoiseTexture)
zox_declare_tag(FrameTexture)
zox_declare_tag(SaveTexture)
zox_declare_tag(DirtTexture)
zox_declare_tag(GrassTexture)
zox_declare_tag(SandTexture)
zox_declare_tag(Tilemap)
zox_memory_component(TextureData, color)
zox_component(TextureSize, int2)
zox_component(TilemapSize, int2)
zox_byte_component(GenerateTexture) 
zox_component(AnimateTexture, double)
zox_entities_component(TextureLinks)
// zoxel_util_includes
#include "util/textures_sdl_util.c"
#include "util/textures_util.c"
// zoxel_prefab_includes
#include "prefabs/noise_texture.c"
#include "prefabs/dirt_texture.c"
// zoxel_system_includes
#include "systems/animate_noise_system.c"
#include "systems/texture_update_system.c"
#include "systems/texture_save_system.c"
#include "systems/noise_texture_system.c"
#include "systems/frame_texture_system.c"
#include "systems/tilemap_generation_system.c"
zox_reset_system(TextureDirtyResetSystem, TextureDirty)
zox_reset_system(GenerateTextureResetSystem, GenerateTexture)
#include "tests/test_texture.c"

zox_begin_module(TexturesCore)
// zoxel_component_defines
zox_define_tag(Texture)
zox_define_tag(NoiseTexture)
zox_define_tag(FrameTexture)
zox_define_tag(SaveTexture)
zox_define_tag(DirtTexture)
zox_define_tag(GrassTexture)
zox_define_tag(SandTexture)
zox_define_tag(Tilemap)
zox_define_component(TextureSize)
zox_define_component(GenerateTexture)
zox_define_component(AnimateTexture)
zox_define_component(TilemapSize)
zox_define_memory_component(TextureData)
zox_define_entities_component(TextureLinks, [in] TextureLinks)
// zoxel_prefab_defines
spawn_prefab_noise_texture(world);
spawn_prefab_texture_dirt(world);
// zoxel_filter_defines
zox_filter(generate_textures2, [none] FrameTexture, [in] GenerateTexture)
// zoxel_system_defines
zox_system(AnimateNoiseSystem, EcsOnUpdate, [out] AnimateTexture, [out] GenerateTexture)
zox_texture_generation_system(NoiseTexture, NoiseTextureSystem)
zox_system_ctx(FrameTextureSystem, EcsPreStore, generate_textures2, [none] FrameTexture, [in] GenerateTexture, [in] TextureSize, [in] Color, [out] TextureData, [out] TextureDirty)
if (!headless) {
    zox_system_1(TextureUpdateSystem, texture_update_pipeline, [out] TextureDirty, [in] TextureData, [in] TextureSize, [in] TextureGPULink)
    texture_update_system_id = ecs_id(TextureUpdateSystem);
}
zox_system(TilemapGenerationSystem, EcsPostUpdate, [none] Tilemap, [in] TilemapSize, [in] TextureLinks, [in] GenerateTexture, [out] TextureSize, [out] TextureData, [out] TextureDirty)
// zox_system_1(TextureSaveSystem, EcsOnUpdate, [in] TextureDirty, [in] TextureData, [in] TextureSize, [none] SaveTexture)
// zox_system_1(AnimateNoiseSystem, EcsOnUpdate, [out] AnimateTexture, [out] GenerateTexture)
zox_define_reset_system(GenerateTextureResetSystem, GenerateTexture)
zoxel_end_module(TexturesCore)

// #include <cstdint> ? https://stackoverflow.com/questions/20024690/is-there-byte-data-type-in-c
// \todo Multithreaded change filters? zox_system

#endif