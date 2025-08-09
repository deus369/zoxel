void TextureGPUDisposeSystem(iter *it) {
    zox_sys_begin()
    zox_sys_in(TextureGPULink)
    for (int i = 0; i < it->count; i++) {
        zox_sys_i(TextureGPULink, textureGPULink)
        if (textureGPULink->value != 0) {
            glDeleteTextures(1, &textureGPULink->value);
        }
    }
} zoxd_system(TextureGPUDisposeSystem)
