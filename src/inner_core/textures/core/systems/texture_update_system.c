void TextureUpdateSystem(ecs_iter_t *it) {
    if (!ecs_query_changed(NULL, it)) return;
    zox_field_in(TextureData, textureDatas, 2)
    zox_field_in(TextureSize, textureSizes, 3)
    zox_field_in(TextureGPULink, textureGPULinks, 4)
    zox_field_out(TextureDirty, textureDirtys, 1)
    for (int i = 0; i < it->count; i++) {
        zox_field_i_out(TextureDirty, textureDirtys, textureDirty)
        if (!textureDirty->value) continue;
        zox_field_i_in(TextureData, textureDatas, textureData)
        zox_field_i_in(TextureSize, textureSizes, textureSize)
        zox_field_i_in(TextureGPULink, textureGPULinks, textureGPULink)
        if (headless) textureDirty->value = 0;
        if (!textureGPULink->value || !textureData->value || textureData->length != textureSize->value.x * textureSize->value.y) continue;
        glBindTexture(GL_TEXTURE_2D, textureGPULink->value);
        glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, textureSize->value.x, textureSize->value.y, 0, GL_RGBA, GL_UNSIGNED_BYTE, textureData->value);
        glBindTexture(GL_TEXTURE_2D, 0);
        textureDirty->value = 0;
        // if (check_opengl_error("TextureUpdateSystem")) break;
    }
} zox_declare_system(TextureUpdateSystem)

// const int texture_type = GL_NEAREST; // GL_NEAREST | GL_LINEAR
//glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, texture_type);
//glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, texture_type);
