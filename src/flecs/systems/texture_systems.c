#define zox_texture_system(system, tag, ...) {\
    zox_filter(textures, [out] textures.core.GenerateTexture, [none] tag)\
    zox_system_ctx(system, zox_pip_textures, textures, [in] textures.core.TextureSize, [out] textures.core.GenerateTexture, [out] rendering.TextureDirty, [out] textures.core.TextureData, __VA_ARGS__, [none] tag)\
}

#define zox_texture_generation_system(texture_tag, system) {\
    zox_filter(generateTextureQuery, [none] texture_tag, [out] textures.core.GenerateTexture)\
    zox_system_ctx(system, zox_pip_textures, generateTextureQuery, [none] texture_tag, [out] rendering.TextureDirty, [out] textures.core.TextureData, [in] textures.core.TextureSize, [out] textures.core.GenerateTexture)\
}

#define zox_texture_generation_system2(texture_tag, system, ...) {\
    zox_filter(generateTextureQuery, [none] texture_tag, [out] textures.core.GenerateTexture)\
    zox_system_ctx(system, zox_pip_textures, generateTextureQuery, [none] texture_tag, [out] rendering.TextureDirty, [out] textures.core.TextureData, [in] textures.core.TextureSize, [out] textures.core.GenerateTexture, __VA_ARGS__)\
}
