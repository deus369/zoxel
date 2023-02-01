#ifndef zoxel_textures_core
#define zoxel_textures_core

const double noise_animation_speed = 0.5;
const unsigned char is_texture_outlines = 0;
zoxel_declare_tag(NoiseTexture)
zoxel_declare_tag(FrameTexture)
zoxel_declare_tag(SaveTexture)
zoxel_declare_tag(DirtTexture)
zoxel_memory_component(Texture, color)  //! A texture with pixels!
zoxel_component(TextureSize, int2)      //! A texture with pixels!
zoxel_byte_component(GenerateTexture)  //! A state for generating textures.
zoxel_component(AnimateTexture, double) //! A state for animating textures.
zoxel_byte_component(TextureDirty)
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

//! textures Module.
/**
*    \todo Multithreaded change filters? zoxel_system
*/
void TexturesCoreImport(ecs_world_t *world)
{
    zoxel_module(TexturesCore)
    zoxel_define_tag(NoiseTexture)
    zoxel_define_tag(FrameTexture)
    zoxel_define_tag(SaveTexture)
    zoxel_define_tag(DirtTexture)
    zoxel_define_component(TextureSize)
    zoxel_define_component(GenerateTexture)
    zoxel_define_component(AnimateTexture)
    zoxel_define_component(TextureDirty)
    zoxel_memory_component_define(Texture)
    zoxel_system_main_thread(world, AnimateNoiseSystem, EcsOnUpdate, [out] AnimateTexture, [out] GenerateTexture);
    zoxel_texture_generation_system(NoiseTexture, NoiseTextureSystem)
    zoxel_texture_generation_system(FrameTexture, FrameTextureSystem)
    zoxel_system_main_thread(world, TextureSaveSystem, EcsOnValidate,
        [in] TextureDirty, [in] Texture, [in] TextureSize, [none] SaveTexture)
    zoxel_reset_system_define(GenerateTextureResetSystem, GenerateTexture)
    zoxel_reset_system_define(TextureDirtyResetSystem, TextureDirty)
    if (!headless)
    {
        zoxel_system_main_thread(world, TextureUpdateSystem, EcsOnValidate,
            [in] TextureDirty, [in] Texture, [in] TextureSize, [in] TextureGPULink)
    }
    spawn_prefab_noise_texture(world);
}
// #include <cstdint> ? https://stackoverflow.com/questions/20024690/is-there-byte-data-type-in-c
#endif