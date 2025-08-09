// TextureRGB's
void TextureRGBUpdateSystem(ecs_iter_t *it) {
    zox_sys_world()
    zox_sys_begin()
    zox_sys_in(TextureData)
    zox_sys_in(TextureSize)
    zox_sys_in(TextureGPULink)
    zox_sys_out(TextureDirty)
    for (int i = 0; i < it->count; i++) {
        zox_sys_e()
        zox_sys_i(TextureData, textureData)
        zox_sys_i(TextureSize, textureSize)
        zox_sys_i(TextureGPULink, textureGPULink)
        zox_sys_o(TextureDirty, textureDirty)
        if (!textureDirty->value) {
            continue;
        }
        if (textureData->length != textureSize->value.x * textureSize->value.y || !textureData->value || !textureGPULink->value) {
            zox_log_error("issue with texture_rgb upload [%s]", zox_get_name(e))
            continue;
        }
        glBindTexture(GL_TEXTURE_2D, textureGPULink->value);
        // different to above
        glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, textureSize->value.x, textureSize->value.y, 0, GL_RGB, GL_UNSIGNED_BYTE, NULL);
        glBindTexture(GL_TEXTURE_2D, 0);
        textureDirty->value = 0;
        // zox_log_error("+ uploaded [%s] size [%ix%i]", zox_get_name(e), textureSize->value.x, textureSize->value.y)
    }
} zoxd_system(TextureRGBUpdateSystem)