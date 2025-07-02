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
    zox_system(MouseTextureSystem, EcsOnUpdate, [in] MouseLock, [in] TextureLink, [in] PlayerLink)
    zox_filter(generate_textures2, [none] FrameTexture, [out] GenerateTexture)
    zox_system(AnimateNoiseSystem, zox_pip_texture_generation, [out] AnimateTexture, [out] GenerateTexture)
    zox_texture_system(NoiseTextureSystem, NoiseTexture, [in] Color)
    zox_texture_generation_system2(FillTexture, FillTextureSystem, [in] Color)
    zox_system_ctx(FrameTextureSystem, zox_pip_texture_generation, generate_textures2, [none] FrameTexture, [out] GenerateTexture, [in] TextureSize, [in] Color, [in] OutlineThickness, [in] FrameCorner, [out] TextureData, [out] TextureDirty)
    zox_system(TilemapGenerationSystem, zox_pip_texture_generation, [in] TilemapSize, [in] TextureLinks, [out] GenerateTexture, [out] TextureSize, [out] TextureData, [out] TextureDirty, [out] TilemapUVs, [none] Tilemap)
    if (!headless) {
        zox_system_1(TextureUpdateSystem, EcsPreStore, [in] TextureData, [in] TextureSize, [in] TextureGPULink, [out] TextureDirty, [none] !TextureRGB)
        zox_system_1(TextureRGBUpdateSystem, EcsPreStore, [in] TextureData, [in] TextureSize, [in] TextureGPULink, [out] TextureDirty, [none] TextureRGB)
    }
}