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
            [out] texturez.GenerateTexture)
    zox_system(AnimateNoiseSystem, zox_pip_texture_generation,
            [out] AnimateTexture,
            [out] texturez.GenerateTexture)
    // zox_texture_system(NoiseTextureSystem, NoiseTexture, [in] colorz.Color)


    zox_filter(fill_texture_query, [none] FillTexture, [out] texturez.GenerateTexture)
    zox_system_ctx(FillTextureSystem, zox_pip_textures, fill_texture_query,
            [in] rendering.TextureSize,
            [in] colorz.Color,
            [out] texturez.TextureData,
            [out] texturez.GenerateTexture,
            [out] rendering.TextureDirty,
            [none] FillTexture)

    // zox_texture_generation_system2(FillTexture, FillTextureSystem, [in] colorz.Color)

    zox_system_ctx(FrameTextureSystem, zox_pip_texture_generation,
            generate_textures2,
            [in] rendering.TextureSize,
            [in] colorz.Color,
            [in] OutlineThickness,
            [in] FrameCorner,
            [out] texturez.GenerateTexture,
            [out] texturez.TextureData,
            [out] rendering.TextureDirty,
            [none] FrameTexture)
    zox_system(TilemapGenerationSystem, zox_pip_texture_generation,
            [in] texturez.TilemapSize,
            [in] texturez.TextureLinks,
            [out] texturez.GenerateTexture,
            [out] rendering.TextureSize,
            [out] texturez.TextureData,
            [out] rendering.TextureDirty,
            [out] TilemapUVs,
            [none] Tilemap)
    if (!headless) {
        zox_system_1(TextureUpdateSystem, EcsPreStore,
                [in] texturez.TextureData,
                [in] rendering.TextureSize,
                [in] rendering.TextureGPULink,
                [out] rendering.TextureDirty,
                [none] !TextureRGB)
        zox_system_1(TextureRGBUpdateSystem, EcsPreStore,
                [in] texturez.TextureData,
                [in] rendering.TextureSize,
                [in] rendering.TextureGPULink,
                [out] rendering.TextureDirty,
                [none] TextureRGB)
    }
}