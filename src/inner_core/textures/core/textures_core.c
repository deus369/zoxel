#ifndef Zoxel_TexturesCore
#define Zoxel_TexturesCore
//! textures Module.

// Settings
const double noiseAnimationSpeed = 0.25;
// Tags
ECS_DECLARE(NoiseTexture);
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
// prefabs
#include "prefabs/NoiseTexture.c"
// util
#include "util/TexturesSDL.c"
// systems
#include "systems/animate_noise_system.c"
#include "systems/generate_texture_reset_system.c"
#include "systems/noise_texture_system.c"
#include "systems/texture_dirty_system.c"
#include "systems/texture_update_system.c"
// tests
#include "tests/TestTexture.c"

//! \todo Multithreaded change filters? zoxel_system

void TexturesCoreImport(ecs_world_t *world)
{
    ECS_MODULE(world, TexturesCore);
    ECS_TAG_DEFINE(world, NoiseTexture);
    zoxel_memory_component_define(world, Texture);
    ECS_COMPONENT_DEFINE(world, TextureSize);
    ECS_COMPONENT_DEFINE(world, GenerateTexture);
    ECS_COMPONENT_DEFINE(world, AnimateTexture);
    ECS_SYSTEM_DEFINE(world, AnimateNoiseSystem, EcsOnUpdate, [out] AnimateTexture, [out] GenerateTexture);
    zoxel_filter(generateTextureQuery, world, [none] NoiseTexture, [in] GenerateTexture);
    zoxel_system_ctx(world, NoiseTextureSystem, EcsOnUpdate, generateTextureQuery,
        [none] NoiseTexture, [out] generic.EntityDirty, [out] Texture, [in] TextureSize, [in] GenerateTexture);
    // zoxel_filter(textureDirtyQuery, world, [none] NoiseTexture, [in] EntityDirty);
    zoxel_system_main_thread(world, GenerateTextureResetSystem, EcsPostUpdate, [out] GenerateTexture);
    ECS_SYSTEM_DEFINE(world, TextureUpdateSystem, EcsOnValidate, [in] generic.EntityDirty, [in] Texture, [in] TextureSize, [in] TextureGPULink);
    // ECS_SYSTEM_DEFINE(world, TextureDirtySystem, EcsOnValidate, [in] EntityDirty, [in] Texture, [in] TextureSize);
    SpawnTexturePrefab(world);
}
#endif