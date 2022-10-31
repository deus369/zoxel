#ifndef Zoxel_TexturesCore
#define Zoxel_TexturesCore
//! Textures Module.

// Settings
const double noiseAnimationSpeed = 0.125;

// Tags
ECS_DECLARE(NoiseTexture);
ECS_DECLARE(GenerateNoiseTexture);
// Components
#include "Components/Texture.c"
#include "Components/TextureSize.c"
#include "Components/GenerateTexture.c"
#include "Components/AnimateTexture.c"
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
    // Tags
    ECS_TAG_DEFINE(world, NoiseTexture);
    // Components
    ZOXEL_DEFINE_MEMORY_COMPONENT(world, Texture);
    ECS_COMPONENT_DEFINE(world, TextureSize);
    ECS_COMPONENT_DEFINE(world, GenerateTexture);
    ECS_COMPONENT_DEFINE(world, AnimateTexture);
    // Queries
    ecs_query_t *generateTextureQuery = ecs_query_init(world, &(ecs_query_desc_t) {
        .filter.terms = {
            { ecs_id(NoiseTexture), .inout = EcsInOutNone },
            { ecs_id(GenerateTexture), .inout = EcsIn }
        }
    });
    // Systems
    //! \todo Multithreaded change filters? ZOXEL_SYSTEM_MULTITHREADED
    ECS_SYSTEM_DEFINE(world, AnimateNoiseSystem, EcsOnUpdate, [out] AnimateTexture, [out] GenerateTexture);
    ECS_SYSTEM_DEFINE(world, NoiseTextureSystem, EcsOnUpdate,
        [none] NoiseTexture, [out] EntityDirty, [out] Texture, [in] TextureSize, [in] GenerateTexture);
    //! Use seperate filter for change query in NoiseTextureSystem.
    ecs_system(world, {
        .entity = ecs_id(NoiseTextureSystem),
        .ctx = generateTextureQuery
    });
    // ECS_SYSTEM_DEFINE(world, NoiseTextureChangeResetter, EcsPostUpdate, [none] NoiseTexture, [in] GenerateTexture);
    ECS_SYSTEM_DEFINE(world, GenerateTextureResetSystem, EcsPostUpdate, [out] GenerateTexture);
    ECS_SYSTEM_DEFINE(world, TextureUpdateSystem, EcsOnValidate, [in] EntityDirty, [in] Texture, [in] TextureSize, [in] TextureGPULink);
    // ECS_SYSTEM_DEFINE(world, TextureDirtySystem, EcsOnValidate, [in] EntityDirty, [in] Texture, [in] TextureSize);
    // add change query to NoiseTextureSystem
    InitializeNoiseTexturePrefab(world);
}
#endif