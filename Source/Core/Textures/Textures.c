//! Textures Module.
#ifndef Zoxel_Textures
#define Zoxel_Textures

// Prefabs
ecs_entity_t texturePrefab;
// Tags
ECS_DECLARE(NoiseTexture);
ECS_DECLARE(GenerateNoiseTexture);
// Components
#include "Components/Texture.c"
#include "Components/TextureSize.c"
#include "Components/GenerateTexture.c"
// Systems
#include "Systems/NoiseTextureSystem.c"
#include "Systems/TextureDirtySystem.c"

ecs_entity_t SpawnTexturePrefab(ecs_world_t *world)
{
    ecs_entity_t texturePrefab = ecs_new_prefab(world, "Le Texture");
    ecs_add(world, texturePrefab, NoiseTexture);
    ecs_add(world, texturePrefab, EntityDirty);
    ecs_add(world, texturePrefab, GenerateTexture);
    ecs_add(world, texturePrefab, Seed);
    ecs_add(world, texturePrefab, TextureSize);
    ecs_add(world, texturePrefab, Texture);
    ecs_override(world, texturePrefab, Seed);
    ecs_override(world, texturePrefab, Texture);
    ecs_override(world, texturePrefab, EntityDirty);
    ecs_override(world, texturePrefab, GenerateTexture);
    ecs_set(world, texturePrefab, Seed, { 666 });
    ecs_set(world, texturePrefab, EntityDirty, { 0 });
    ecs_set(world, texturePrefab, TextureSize, { 16 * 16, 16 * 16 });
    ecs_set(world, texturePrefab, GenerateTexture, { 1 });
    return texturePrefab;
}

//! Spawn a Player character.
ecs_entity_t SpawnTexture(ecs_world_t *world)
{
    ecs_entity_t textureEntity = ecs_new_w_pair(world, EcsIsA, texturePrefab);
    printf("Spawned Texture [%lu]\n", (long unsigned int) textureEntity);
    return textureEntity;
}

void TexturesImport(ecs_world_t *world)
{
    ECS_MODULE(world, Textures);
    ECS_TAG_DEFINE(world, NoiseTexture);
    ECS_COMPONENT_DEFINE(world, Texture);
    ECS_COMPONENT_DEFINE(world, TextureSize);
    ECS_COMPONENT_DEFINE(world, GenerateTexture);
    ECS_SYSTEM_DEFINE(world, NoiseTextureSystem, EcsOnUpdate,
        [none] NoiseTexture,
        [out] GenerateTexture,
        [out] EntityDirty,
        [out] Texture,
        [in] TextureSize);
    ECS_SYSTEM_DEFINE(world, TextureDirtySystem, EcsOnUpdate,
        [out] EntityDirty,
        [in] Texture,
        [in] TextureSize);
    // ecs_system_enable_multithreading(world, ecs_id(NoiseTextureSystem));
    // ecs_system_enable_multithreading(world, ecs_id(TextureDirtySystem));
    texturePrefab = SpawnTexturePrefab(world);
    SpawnTexture(world);
}

#endif