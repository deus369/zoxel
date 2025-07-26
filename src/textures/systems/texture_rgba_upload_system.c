void TextureUpdateSystem(ecs_iter_t *it) {
    zox_sys_begin()
    zox_sys_in(TextureData)
    zox_sys_in(TextureSize)
    zox_sys_in(TextureGPULink)
    zox_sys_out(TextureDirty)
    for (int i = 0; i < it->count; i++) {
        zox_sys_i(TextureData, textureData)
        zox_sys_i(TextureSize, textureSize)
        zox_sys_i(TextureGPULink, textureGPULink)
        zox_sys_o(TextureDirty, textureDirty)
        if (textureDirty->value == 0 || textureData->length != textureSize->value.x * textureSize->value.y || !textureData->value || !textureGPULink->value) {
            continue;
        }
        glBindTexture(GL_TEXTURE_2D, textureGPULink->value);
        glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, textureSize->value.x, textureSize->value.y, 0, GL_RGBA, GL_UNSIGNED_BYTE, textureData->value);
        glBindTexture(GL_TEXTURE_2D, 0);
        textureDirty->value = 0;
    }
} zox_declare_system(TextureUpdateSystem)