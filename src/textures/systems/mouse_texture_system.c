void MouseTextureSystem(ecs_iter_t *it) {
    zox_sys_world()
    zox_sys_begin()
    zox_sys_in(MouseLock)
    zox_sys_in(TextureLink)
    zox_sys_in(PlayerLink)
    for (int i = 0; i < it->count; i++) {
        zox_sys_i(TextureLink, textureLink)
        if (!textureLink->value) {
            continue;
        }
        zox_sys_i(PlayerLink, playerLink)
        zox_sys_i(MouseLock, mouseLock)
        zox_set(textureLink->value, RenderDisabled, { mouseLock->value || playerLink->value == 0 })
    }
} zox_declare_system(MouseTextureSystem)
