#ifndef Zoxel_TexturesCore
#define Zoxel_TexturesCore
//! Textures Module.

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
    ECS_TAG_DEFINE(world, NoiseTexture);
    ZOXEL_DEFINE_MEMORY_COMPONENT(world, Texture);
    ECS_COMPONENT_DEFINE(world, TextureSize);
    ECS_COMPONENT_DEFINE(world, GenerateTexture);
    ECS_COMPONENT_DEFINE(world, AnimateTexture);
    ZOXEL_SYSTEM_MULTITHREADED(world, GenerateTextureResetSystem, EcsPostUpdate, [out] GenerateTexture);
    ZOXEL_SYSTEM_MULTITHREADED(world, AnimateNoiseSystem, EcsOnUpdate, [out] AnimateTexture, [out] GenerateTexture);
    ECS_SYSTEM_DEFINE(world, NoiseTextureSystem, EcsOnUpdate,
        [none] NoiseTexture, [out] EntityDirty, [out] Texture, [in] GenerateTexture, [in] TextureSize);
    ECS_SYSTEM_DEFINE(world, TextureDirtySystem, EcsOnValidate, [in] EntityDirty, [in] Texture, [in] TextureSize);
    ECS_SYSTEM_DEFINE(world, TextureUpdateSystem, EcsOnValidate, [in] EntityDirty, [in] Texture, [in] TextureSize);
    InitializeNoiseTexturePrefab(world);
}
#endif