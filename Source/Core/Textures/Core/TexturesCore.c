#ifndef Zoxel_TexturesCore
#define Zoxel_TexturesCore
//! Textures Module.
/**
 * \todo Use ViewMatrix hooks here to handle texture memories.
*/

// Tags
ECS_DECLARE(NoiseTexture);
ECS_DECLARE(GenerateNoiseTexture);
// Components
#include "Components/Texture.c"
#include "Components/TextureSize.c"
#include "Components/GenerateTexture.c"
// Prefabs
#include "Prefabs/NoiseTexture.c"
// Util
#include "Util/TexturesSDL.c"
// Systems
#include "Systems/NoiseTextureSystem.c"
#include "Systems/TextureDirtySystem.c"

//! Spawn a Player character.
ecs_entity_t SpawnTexture(ecs_world_t *world, ecs_entity_t prefab)
{
    ecs_entity_t textureEntity = ecs_new_w_pair(world, EcsIsA, prefab);
    printf("Spawned Texture [%lu]\n", (long unsigned int) textureEntity);
    return textureEntity;
}

void TexturesCoreImport(ecs_world_t *world)
{
    ECS_MODULE(world, TexturesCore);
    ECS_TAG_DEFINE(world, NoiseTexture);
    ECS_COMPONENT_DEFINE(world, Texture);
    ECS_COMPONENT_DEFINE(world, TextureSize);
    ECS_COMPONENT_DEFINE(world, GenerateTexture);
    ECS_SYSTEM_DEFINE(world, NoiseTextureSystem, EcsOnUpdate,
        [none] NoiseTexture,
        [out] GenerateTexture, [out] EntityDirty,
        [out] Texture, [in] TextureSize);
    ECS_SYSTEM_DEFINE(world, TextureDirtySystem, EcsOnValidate,
        [in] EntityDirty, [in] Texture, [in] TextureSize);
    // Testing!
    InitializeNoiseTexturePrefab(world);
    SpawnTexture(world, noiseTexturePrefab);
}

#endif