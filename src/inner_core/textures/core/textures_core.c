#ifndef zoxel_textures_core
#define zoxel_textures_core

#include "settings/settings.c"
zox_declare_tag(Texture)
zox_declare_tag(NoiseTexture)
zox_declare_tag(FrameTexture)
zox_declare_tag(SaveTexture)
zox_declare_tag(DirtTexture)
zox_memory_component(TextureData, color)
zox_component(TextureSize, int2)
zox_byte_component(GenerateTexture) 
zox_component(AnimateTexture, double)
#include "util/textures_sdl_util.c"
#include "util/textures_util.c"
#include "prefabs/noise_texture.c"
#include "systems/animate_noise_system.c"
#include "systems/texture_update_system.c"
#include "systems/texture_save_system.c"
#include "systems/noise_texture_system.c"
#include "systems/frame_texture_system.c"
zox_reset_system(TextureDirtyResetSystem, TextureDirty)
zox_reset_system(GenerateTextureResetSystem, GenerateTexture)
#include "tests/test_texture.c"

zox_begin_module(TexturesCore)
zox_define_tag(Texture)
zox_define_tag(NoiseTexture)
zox_define_tag(FrameTexture)
zox_define_tag(SaveTexture)
zox_define_tag(DirtTexture)
zox_define_component(TextureSize)
zox_define_component(GenerateTexture)
zox_define_component(AnimateTexture)
zox_define_memory_component(TextureData)
// zox_system_1(AnimateNoiseSystem, EcsOnUpdate, [out] AnimateTexture, [out] GenerateTexture)
zox_system(AnimateNoiseSystem, EcsOnUpdate, [out] AnimateTexture, [out] GenerateTexture)
zox_texture_generation_system(NoiseTexture, NoiseTextureSystem)
// zox_texture_generation_system(FrameTexture, FrameTextureSystem)
zox_filter(generate_textures2, [none] FrameTexture, [in] GenerateTexture)
zox_system_ctx(FrameTextureSystem, EcsPreStore, generate_textures2, [none] FrameTexture, [in] GenerateTexture, [in] TextureSize, [in] Color, [out] TextureData, [out] TextureDirty)
// zox_system_1(TextureSaveSystem, texture_update_pipeline, [in] TextureDirty, [in] TextureData, [in] TextureSize, [none] SaveTexture)
// zox_system(TextureSaveSystem, texture_update_pipeline, [in] TextureDirty, [in] TextureData, [in] TextureSize, [none] SaveTexture)
if (!headless) {
    zox_system_1(TextureUpdateSystem, texture_update_pipeline, [out] TextureDirty, [in] TextureData, [in] TextureSize, [in] TextureGPULink)
    texture_update_system_id = ecs_id(TextureUpdateSystem);
}
zox_define_reset_system(GenerateTextureResetSystem, GenerateTexture)
// zox_define_reset_system(TextureDirtyResetSystem, TextureDirty)
spawn_prefab_noise_texture(world);
zoxel_end_module(TexturesCore)

// #include <cstdint> ? https://stackoverflow.com/questions/20024690/is-there-byte-data-type-in-c
// \todo Multithreaded change filters? zox_system

#endif