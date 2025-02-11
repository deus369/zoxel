void TextureUpdateSystem(ecs_iter_t *it) {
    zox_field_in(TextureData, textureDatas, 1)
    zox_field_in(TextureSize, textureSizes, 2)
    zox_field_in(TextureGPULink, textureGPULinks, 3)
    zox_field_out(TextureDirty, textureDirtys, 4)
    for (int i = 0; i < it->count; i++) {
        zox_field_o(TextureDirty, textureDirtys, textureDirty)
        if (textureDirty->value == 0) continue;
        zox_field_i(TextureData, textureDatas, textureData)
        zox_field_i(TextureSize, textureSizes, textureSize)
        if (textureData->length != textureSize->value.x * textureSize->value.y) {
            zox_log("! texture upload - texture length missmatch\n")
            continue;
        }
        if (!textureData->value) {
            // zox_log("! texture upload [%s] - texture data not initialized\n", zox_get_name(it->entities[i]))
            // textureDirty->value = 0;
            continue;
        }
        zox_field_i(TextureGPULink, textureGPULinks, textureGPULink)
        if (!textureGPULink->value) {
            zox_log("! texture upload - texture gpu link issue\n")
            continue;
        }
        zox_field_e()
        glBindTexture(GL_TEXTURE_2D, textureGPULink->value);
        if (zox_has(e, TextureRGB)) {
            // todo: textureData definitely not gonna work here! make a seperate TextureData for RGB data
            glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, textureSize->value.x, textureSize->value.y, 0, GL_RGB, GL_UNSIGNED_BYTE, NULL); //  textureData->value);
        } else {
            glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, textureSize->value.x, textureSize->value.y, 0, GL_RGBA, GL_UNSIGNED_BYTE, textureData->value);
        }
        glBindTexture(GL_TEXTURE_2D, 0);
        textureDirty->value = 0;
    }
} zox_declare_system(TextureUpdateSystem)
