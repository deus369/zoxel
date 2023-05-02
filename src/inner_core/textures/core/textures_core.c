#ifndef zoxel_textures_core
#define zoxel_textures_core

#include "settings/settings.c"
zoxel_declare_tag(Texture)
zoxel_declare_tag(NoiseTexture)
zoxel_declare_tag(FrameTexture)
zoxel_declare_tag(SaveTexture)
zoxel_declare_tag(DirtTexture)
zoxel_memory_component(TextureData, color)
zoxel_component(TextureSize, int2)
zoxel_byte_component(GenerateTexture) 
zoxel_component(AnimateTexture, double)
#include "util/textures_sdl_util.c"
#include "util/textures_util.c"
#include "prefabs/noise_texture.c"
#include "systems/animate_noise_system.c"
#include "systems/texture_update_system.c"
#include "systems/texture_save_system.c"
#include "systems/noise_texture_system.c"
#include "systems/frame_texture_system.c"
zoxel_reset_system(TextureDirtyResetSystem, TextureDirty)
zoxel_reset_system(GenerateTextureResetSystem, GenerateTexture)
#include "tests/test_texture.c"

zoxel_begin_module(TexturesCore)
zoxel_define_tag(Texture)
zoxel_define_tag(NoiseTexture)
zoxel_define_tag(FrameTexture)
zoxel_define_tag(SaveTexture)
zoxel_define_tag(DirtTexture)
zoxel_define_component(TextureSize)
zoxel_define_component(GenerateTexture)
zoxel_define_component(AnimateTexture)
zoxel_define_memory_component(TextureData)
// zoxel_system_1(AnimateNoiseSystem, EcsOnUpdate, [out] AnimateTexture, [out] GenerateTexture)
zoxel_system(AnimateNoiseSystem, EcsOnUpdate, [out] AnimateTexture, [out] GenerateTexture)
zoxel_texture_generation_system(NoiseTexture, NoiseTextureSystem)
// zoxel_texture_generation_system(FrameTexture, FrameTextureSystem)
zoxel_filter(generate_textures2, world, [none] FrameTexture, [in] GenerateTexture)
zoxel_system_ctx(FrameTextureSystem, EcsPreStore, generate_textures2, [none] FrameTexture,
    [in] GenerateTexture, [in] TextureSize, [in] Color, [out] TextureData, [out] TextureDirty)
// zoxel_system_1(TextureSaveSystem, texture_update_pipeline, [in] TextureDirty, [in] TextureData, [in] TextureSize, [none] SaveTexture)
// zoxel_system(TextureSaveSystem, texture_update_pipeline, [in] TextureDirty, [in] TextureData, [in] TextureSize, [none] SaveTexture)
if (!headless) {
    zoxel_system_1(TextureUpdateSystem, texture_update_pipeline, [out] TextureDirty, [in] TextureData, [in] TextureSize, [in] TextureGPULink)
    texture_update_system_id = ecs_id(TextureUpdateSystem);
}
zoxel_define_reset_system(GenerateTextureResetSystem, GenerateTexture)
// zoxel_define_reset_system(TextureDirtyResetSystem, TextureDirty)
spawn_prefab_noise_texture(world);
zoxel_end_module(TexturesCore)

// #include <cstdint> ? https://stackoverflow.com/questions/20024690/is-there-byte-data-type-in-c
// \todo Multithreaded change filters? zoxel_system

#endif