#define zox_texture_system(system, tag, ...) {\
    zox_filter(textures, [out] texturez.GenerateTexture, [none] tag)\
    zox_system_ctx(system, zox_pip_textures, textures, [in] rendering.TextureSize, [out] texturez.GenerateTexture, [out] rendering.TextureDirty, [out] texturez.TextureData, __VA_ARGS__, [none] tag)\
}

#define zox_texture_generation_system(texture_tag, system) {\
    zox_filter(generateTextureQuery, [none] texture_tag, [out] texturez.GenerateTexture)\
    zox_system_ctx(system, zox_pip_textures, generateTextureQuery, [none] texture_tag, [out] rendering.TextureDirty, [out] texturez.TextureData, [in] rendering.TextureSize, [out] texturez.GenerateTexture)\
}

#define zox_texture_generation_system2(texture_tag, system, ...) {\
    zox_filter(generateTextureQuery, [none] texture_tag, [out] texturez.GenerateTexture)\
    zox_system_ctx(system, zox_pip_textures, generateTextureQuery, [none] texture_tag, [out] rendering.TextureDirty, [out] texturez.TextureData, [in] rendering.TextureSize, [out] texturez.GenerateTexture, __VA_ARGS__)\
}
