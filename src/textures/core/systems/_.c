#include "animate_noise_system.c"
#include "texture_rgb_upload_system.c"
#include "texture_rgba_upload_system.c"
#include "noise_texture_system.c"
#include "fill_texture_system.c"
#include "frame_texture_system.c"
#include "tilemap_generation_system.c"
#include "mouse_texture_system.c"
zox_increment_system_with_reset(GenerateTexture, zox_generate_texture_end)

void define_systems_textures(ecs_world_t *world) {
    zox_define_increment_system(GenerateTexture, EcsOnLoad, [none] Texture)
    zox_system(MouseTextureSystem, EcsOnUpdate,
        [in] inputs.MouseLock,
        [in] TextureLink,
        [in] players.PlayerLink)
    zox_filter(generate_textures2,
        [none] FrameTexture,
        [out] textures.core.GenerateTexture)
    zox_system(AnimateNoiseSystem, zox_pip_texture_generation,
        [out] AnimateTexture,
        [out] textures.core.GenerateTexture)
    zox_texture_system(NoiseTextureSystem, NoiseTexture,
        [in] colorz.Color)
    zox_texture_generation_system2(FillTexture, FillTextureSystem,
        [in] colorz.Color)
    zox_system_ctx(FrameTextureSystem, zox_pip_texture_generation, generate_textures2,
        [none] FrameTexture,
        [out] textures.core.GenerateTexture,
        [in] textures.core.TextureSize,
        [in] colorz.Color,
        [in] OutlineThickness,
        [in] FrameCorner,
        [out] textures.core.TextureData,
        [out] rendering.TextureDirty)
    zox_system(TilemapGenerationSystem, zox_pip_texture_generation,
        [in] textures.core.TilemapSize,
        [in] textures.core.TextureLinks,
        [out] textures.core.GenerateTexture,
        [out] textures.core.TextureSize,
        [out] textures.core.TextureData,
        [out] rendering.TextureDirty,
        [out] TilemapUVs,
        [none] Tilemap)
    if (!headless) {
        zox_system_1(TextureUpdateSystem, EcsPreStore,
            [in] textures.core.TextureData,
            [in] textures.core.TextureSize,
            [in] rendering.core.TextureGPULink,
            [out] rendering.TextureDirty,
            [none] !TextureRGB)
        zox_system_1(TextureRGBUpdateSystem, EcsPreStore,
            [in] textures.core.TextureData,
            [in] textures.core.TextureSize,
            [in] rendering.core.TextureGPULink,
            [out] rendering.TextureDirty,
            [none] TextureRGB)
    }
}