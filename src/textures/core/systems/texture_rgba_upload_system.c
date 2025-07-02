void TextureUpdateSystem(ecs_iter_t *it) {
    zox_field_in(TextureData, textureDatas, 1)
    zox_field_in(TextureSize, textureSizes, 2)
    zox_field_in(TextureGPULink, textureGPULinks, 3)
    zox_field_out(TextureDirty, textureDirtys, 4)
    for (int i = 0; i < it->count; i++) {
        zox_field_i(TextureData, textureDatas, textureData)
        zox_field_i(TextureSize, textureSizes, textureSize)
        zox_field_i(TextureGPULink, textureGPULinks, textureGPULink)
        zox_field_o(TextureDirty, textureDirtys, textureDirty)
        if (textureDirty->value == 0 || textureData->length != textureSize->value.x * textureSize->value.y || !textureData->value || !textureGPULink->value) {
            continue;
        }
        glBindTexture(GL_TEXTURE_2D, textureGPULink->value);
        // rgba
        glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, textureSize->value.x, textureSize->value.y, 0, GL_RGBA, GL_UNSIGNED_BYTE, textureData->value);
        glBindTexture(GL_TEXTURE_2D, 0);
        textureDirty->value = 0;
    }
} zox_declare_system(TextureUpdateSystem)