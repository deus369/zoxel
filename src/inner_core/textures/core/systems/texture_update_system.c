void TextureUpdateSystem(ecs_iter_t *it) {
    if (!ecs_query_changed(NULL, it)) return;
    zox_field_in(TextureData, textureDatas, 1)
    zox_field_in(TextureSize, textureSizes, 2)
    zox_field_in(TextureGPULink, textureGPULinks, 3)
    zox_field_out(TextureDirty, textureDirtys, 4)
    for (int i = 0; i < it->count; i++) {
        zox_field_o(TextureDirty, textureDirtys, textureDirty)
        if (!textureDirty->value) continue;
        zox_field_i(TextureData, textureDatas, textureData)
        zox_field_i(TextureSize, textureSizes, textureSize)
        zox_field_i(TextureGPULink, textureGPULinks, textureGPULink)
        if (!textureGPULink->value || !textureData->value || textureData->length != textureSize->value.x * textureSize->value.y) continue;
        glBindTexture(GL_TEXTURE_2D, textureGPULink->value);
        if (zox_has(it->entities[i], TextureRGB)) {
            // textureData definitely not gonna work here!
            glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, textureSize->value.x, textureSize->value.y, 0, GL_RGB, GL_UNSIGNED_BYTE, NULL); //  textureData->value);
            /*glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
            glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
            glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
            glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);*/
        } else {
            glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, textureSize->value.x, textureSize->value.y, 0, GL_RGBA, GL_UNSIGNED_BYTE, textureData->value);
        }
        glBindTexture(GL_TEXTURE_2D, 0);
        textureDirty->value = 0;
    }
} zox_declare_system(TextureUpdateSystem)

// const int texture_type = GL_NEAREST; // GL_NEAREST | GL_LINEAR
//glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, texture_type);
//glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, texture_type);
