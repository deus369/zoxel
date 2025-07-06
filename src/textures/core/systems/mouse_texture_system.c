// how to link main_window, viewport_dimensions and mouse
// byte has_disabled_sdl_mouse_cursor = 0;
void MouseTextureSystem(ecs_iter_t *it) {
    zox_field_world()
    zox_field_in(MouseLock, mouseLocks, 1)
    zox_field_in(TextureLink, textureLinks, 2)
    zox_field_in(PlayerLink, playerLinks, 3)
    for (int i = 0; i < it->count; i++) {
        zox_field_i(TextureLink, textureLinks, textureLink)
        if (!textureLink->value) {
            continue;
        }
        zox_field_i(PlayerLink, playerLinks, playerLink)
        zox_field_i(MouseLock, mouseLocks, mouseLock)
        zox_set(textureLink->value, RenderDisabled, { mouseLock->value || playerLink->value == 0 })
    }
} zox_declare_system(MouseTextureSystem)
