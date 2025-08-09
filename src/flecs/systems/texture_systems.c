#define zox_texture_system(system, tag, ...) {\
    zox_filter(textures, [out] textures.GenerateTexture, [none] tag)\
    zox_system_ctx(system, zoxp_textures, textures, [in] rendering.TextureSize, [out] textures.GenerateTexture, [out] rendering.TextureDirty, [out] textures.TextureData, __VA_ARGS__, [none] tag)\
}

#define zox_texture_generation_system(texture_tag, system) {\
    zox_filter(generateTextureQuery, [none] texture_tag, [out] textures.GenerateTexture)\
    zox_system_ctx(system, zoxp_textures, generateTextureQuery, [none] texture_tag, [out] rendering.TextureDirty, [out] textures.TextureData, [in] rendering.TextureSize, [out] textures.GenerateTexture)\
}

#define zox_texture_generation_system2(texture_tag, system, ...) {\
    zox_filter(generateTextureQuery, [none] texture_tag, [out] textures.GenerateTexture)\
    zox_system_ctx(system, zoxp_textures, generateTextureQuery, [none] texture_tag, [out] rendering.TextureDirty, [out] textures.TextureData, [in] rendering.TextureSize, [out] textures.GenerateTexture, __VA_ARGS__)\
}
