

// TextureRGB's
void TextureRGBUpdateSystem(ecs_iter_t *it) {
    zox_sys_world()
    zox_field_in(TextureData, textureDatas, 1)
    zox_field_in(TextureSize, textureSizes, 2)
    zox_field_in(TextureGPULink, textureGPULinks, 3)
    zox_field_out(TextureDirty, textureDirtys, 4)
    for (int i = 0; i < it->count; i++) {
        zox_sys_e()
        zox_field_i(TextureData, textureDatas, textureData)
        zox_field_i(TextureSize, textureSizes, textureSize)
        zox_field_i(TextureGPULink, textureGPULinks, textureGPULink)
        zox_field_o(TextureDirty, textureDirtys, textureDirty)
        if (!textureDirty->value) {
            continue;
        }
        if (textureData->length != textureSize->value.x * textureSize->value.y || !textureData->value || !textureGPULink->value) {
            zox_log_error(" issue with texture_rgb upload [%s]", zox_get_name(e))
            continue;
        }
        glBindTexture(GL_TEXTURE_2D, textureGPULink->value);
        // different to above
        glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, textureSize->value.x, textureSize->value.y, 0, GL_RGB, GL_UNSIGNED_BYTE, NULL);
        glBindTexture(GL_TEXTURE_2D, 0);
        textureDirty->value = 0;
        // zox_log_error("+ uploaded [%s] size [%ix%i]", zox_get_name(e), textureSize->value.x, textureSize->value.y)
    }
} zox_declare_system(TextureRGBUpdateSystem)