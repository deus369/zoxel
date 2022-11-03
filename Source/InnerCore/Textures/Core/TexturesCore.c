#ifndef Zoxel_TexturesCore
#define Zoxel_TexturesCore
//! Textures Module.

// Settings
const double noiseAnimationSpeed = 0.125;
// Tags
ECS_DECLARE(NoiseTexture);
// ECS_DECLARE(GenerateNoiseTexture);
// Components
//! A texture with pixels!
zoxel_memory_component(Texture, color);
// #include <cstdint> ? https://stackoverflow.com/questions/20024690/is-there-byte-data-type-in-c
//! A texture with pixels!
zoxel_component(TextureSize, int2);
//! A state for generating textures.
zoxel_component(GenerateTexture, unsigned char);
//! A state for animating textures.
zoxel_component(AnimateTexture, double);
// Prefabs
#include "Prefabs/NoiseTexture.c"
// Util
#include "Util/TexturesSDL.c"
// Systems
#include "Systems/GenerateTextureResetSystem.c"
#include "Systems/NoiseTextureSystem.c"
#include "Systems/TextureDirtySystem.c"
#include "Systems/TextureUpdateSystem.c"
#include "Systems/AnimateNoiseSystem.c"
// Tests
#include "Tests/TestTexture.c"

void TexturesCoreImport(ecs_world_t *world)
{
    ECS_MODULE(world, TexturesCore);
    ECS_TAG_DEFINE(world, NoiseTexture);
    zoxel_memory_component_define(world, Texture);
    ECS_COMPONENT_DEFINE(world, TextureSize);
    ECS_COMPONENT_DEFINE(world, GenerateTexture);
    ECS_COMPONENT_DEFINE(world, AnimateTexture);
    // Systems
    //! \todo Multithreaded change filters? zoxel_system
    ECS_SYSTEM_DEFINE(world, AnimateNoiseSystem, EcsOnUpdate, [out] AnimateTexture, [out] GenerateTexture);
    //! Use seperate filter for change query in NoiseTextureSystem.
    zoxel_filter(generateTextureQuery, world, [none] NoiseTexture, [in] GenerateTexture);
    zoxel_system_ctx(world, NoiseTextureSystem, EcsOnUpdate, generateTextureQuery,
        [none] NoiseTexture, [out] EntityDirty, [out] Texture, [in] TextureSize, [in] GenerateTexture);
    // ECS_SYSTEM_DEFINE(world, NoiseTextureChangeResetter, EcsPostUpdate, [none] NoiseTexture, [in] GenerateTexture);
    ECS_SYSTEM_DEFINE(world, GenerateTextureResetSystem, EcsPostUpdate, [out] GenerateTexture);
    ECS_SYSTEM_DEFINE(world, TextureUpdateSystem, EcsOnValidate, [in] EntityDirty, [in] Texture, [in] TextureSize, [in] TextureGPULink);
    // ECS_SYSTEM_DEFINE(world, TextureDirtySystem, EcsOnValidate, [in] EntityDirty, [in] Texture, [in] TextureSize);
    // add change query to NoiseTextureSystem
    SpawnTexturePrefab(world);
}
#endif