#ifndef zoxel_textures_core
#define zoxel_textures_core
//! textures Module.

// Settings
const double noiseAnimationSpeed = 0.5;
// Tags
ECS_DECLARE(NoiseTexture);
ECS_DECLARE(FrameTexture);
// ECS_DECLARE(GenerateNoiseTexture);
// components
//! A texture with pixels!
zoxel_memory_component(Texture, color);
// #include <cstdint> ? https://stackoverflow.com/questions/20024690/is-there-byte-data-type-in-c
//! A texture with pixels!
zoxel_component(TextureSize, int2);
//! A state for generating textures.
zoxel_component(GenerateTexture, unsigned char);
//! A state for animating textures.
zoxel_component(AnimateTexture, double);
// util
#include "util/textures_sdl_util.c"
#include "util/textures_util.c"
// prefabs
#include "prefabs/noise_texture.c"
// systems
#include "systems/animate_noise_system.c"
#include "systems/generate_texture_reset_system.c"
#include "systems/texture_dirty_system.c"
#include "systems/texture_update_system.c"
// texture generation systems
#include "systems/noise_texture_system.c"
#include "systems/frame_texture_system.c"
// tests
#include "tests/TestTexture.c"

#define add_texture_generation_system(texture_tag, system)\
{\
    zoxel_filter(generateTextureQuery, world, [none] texture_tag, [in] GenerateTexture);\
    zoxel_system_ctx(world, system, EcsOnUpdate, generateTextureQuery,\
        [none] texture_tag, [out] generic.EntityDirty, [out] Texture, [in] TextureSize, [in] GenerateTexture);\
}

//! \todo Multithreaded change filters? zoxel_system
void TexturesCoreImport(ecs_world_t *world)
{
    ECS_MODULE(world, TexturesCore);
    ECS_TAG_DEFINE(world, NoiseTexture);
    ECS_TAG_DEFINE(world, FrameTexture);
    zoxel_memory_component_define(world, Texture);
    ECS_COMPONENT_DEFINE(world, TextureSize);
    ECS_COMPONENT_DEFINE(world, GenerateTexture);
    ECS_COMPONENT_DEFINE(world, AnimateTexture);
    ECS_SYSTEM_DEFINE(world, AnimateNoiseSystem, EcsOnUpdate, [out] AnimateTexture, [out] GenerateTexture);
    add_texture_generation_system(NoiseTexture, NoiseTextureSystem);
    add_texture_generation_system(FrameTexture, FrameTextureSystem);
    zoxel_system_main_thread(world, GenerateTextureResetSystem, EcsPostUpdate, [out] GenerateTexture);
    ECS_SYSTEM_DEFINE(world, TextureUpdateSystem, EcsOnValidate, [in] generic.EntityDirty, [in] Texture, [in] TextureSize, [in] TextureGPULink);
    SpawnTexturePrefab(world);
}

/*zoxel_filter(generateTextureQuery, world, [none] NoiseTexture, [in] GenerateTexture);
zoxel_system_ctx(world, NoiseTextureSystem, EcsOnUpdate, generateTextureQuery,
    [none] NoiseTexture, [out] generic.EntityDirty, [out] Texture, [in] TextureSize, [in] GenerateTexture);*/
// zoxel_filter(textureDirtyQuery, world, [none] NoiseTexture, [in] EntityDirty);
// ECS_SYSTEM_DEFINE(world, TextureDirtySystem, EcsOnValidate, [in] EntityDirty, [in] Texture, [in] TextureSize);
#endif