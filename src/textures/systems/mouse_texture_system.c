void MouseTextureSystem(ecs_iter_t *it) {
    zox_sys_world()
    zox_sys_begin()
    zox_sys_in(MouseLock)
    zox_sys_in(TextureLink)
    zox_sys_in(DeviceDisabled)
    for (int i = 0; i < it->count; i++) {
        zox_sys_i(TextureLink, textureLink)
        zox_sys_i(MouseLock, mouseLock)
        zox_sys_i(DeviceDisabled, deviceDisabled)
        if (textureLink->value) {
            byte render_disabled = mouseLock->value || deviceDisabled->value;
            zox_set(textureLink->value, RenderDisabled, { render_disabled })
        }
    }
} zox_declare_system(MouseTextureSystem)
