#ifndef zoxel_textures_core
#define zoxel_textures_core

// Settings
const double noise_animation_speed = 0.5;
const bool is_texture_outlines = false;
// Tags
ECS_DECLARE(NoiseTexture);
ECS_DECLARE(FrameTexture);
ECS_DECLARE(SaveTexture);
ECS_DECLARE(DirtTexture);
// components
//! A texture with pixels!
zoxel_memory_component(Texture, color);
// #include <cstdint> ? https://stackoverflow.com/questions/20024690/is-there-byte-data-type-in-c
//! A texture with pixels!
zoxel_component(TextureSize, int2);
//! A state for generating textures.
zoxel_state_component(GenerateTexture);
//! A state for animating textures.
zoxel_component(AnimateTexture, double);
zoxel_state_component(TextureDirty);
// util
#include "util/textures_sdl_util.c"
#include "util/textures_util.c"
// prefabs
#include "prefabs/noise_texture.c"
// systems
#include "systems/animate_noise_system.c"
// #include "systems/generate_texture_reset_system.c"
#include "systems/texture_update_system.c"
#include "systems/texture_save_system.c"
// texture generation systems
#include "systems/noise_texture_system.c"
#include "systems/frame_texture_system.c"
zoxel_reset_system(TextureDirtyResetSystem, TextureDirty)
zoxel_reset_system(GenerateTextureResetSystem, GenerateTexture)
// tests
#include "tests/test_texture.c"

//! textures Module.
/**
*    \todo Multithreaded change filters? zoxel_system
*/
void TexturesCoreImport(ecs_world_t *world)
{
    ECS_MODULE(world, TexturesCore);
    ECS_TAG_DEFINE(world, NoiseTexture);
    ECS_TAG_DEFINE(world, FrameTexture);
    ECS_TAG_DEFINE(world, SaveTexture);
    ECS_TAG_DEFINE(world, DirtTexture);
    zoxel_memory_component_define(world, Texture);
    ECS_COMPONENT_DEFINE(world, TextureSize);
    ECS_COMPONENT_DEFINE(world, GenerateTexture);
    ECS_COMPONENT_DEFINE(world, AnimateTexture);
    ECS_COMPONENT_DEFINE(world, TextureDirty);
    zoxel_system_main_thread(world, AnimateNoiseSystem, EcsOnUpdate, [out] AnimateTexture, [out] GenerateTexture);
    zoxel_texture_generation_system(NoiseTexture, NoiseTextureSystem);
    zoxel_texture_generation_system(FrameTexture, FrameTextureSystem);
    zoxel_system_main_thread(world, TextureSaveSystem, EcsOnValidate,
        [in] TextureDirty, [in] Texture, [in] TextureSize, [none] SaveTexture);
    zoxel_system_main_thread(world, TextureUpdateSystem, EcsOnValidate,
        [in] TextureDirty, [in] Texture, [in] TextureSize, [in] TextureGPULink);
    zoxel_reset_system_define(GenerateTextureResetSystem, GenerateTexture);
    zoxel_reset_system_define(TextureDirtyResetSystem, TextureDirty);
    // prefabs
    spawn_prefab_noise_texture(world);
}
#endif