// animation system
void ElementActiveSystem(ecs_iter_t *it) {
    zox_sys_begin()
    zox_sys_in(ActiveState);
    zox_sys_in(ActiveStateDirty);
    // zox_sys_in(ActiveColor);
    //zox_sys_out(Color);
    zox_sys_out(OutlineColor);
    zox_sys_out(Brightness);
    zox_sys_out(GenerateTexture);
    for (int i = 0; i < it->count; i++) {
        zox_sys_i(ActiveState, activeState);
        zox_sys_i(ActiveStateDirty, activeStateDirty);
        //zox_sys_o(Color, colorc);
        zox_sys_o(OutlineColor, outline);
        zox_sys_o(Brightness, brightness);
        zox_sys_o(GenerateTexture, generateTexture);
        if (activeStateDirty->value != zox_dirty_active) {
            continue;
        }
        brightness->value = activeState->value ? ui_active_brightness : ui_default_brightness;
        outline->value = activeState->value ? color_purple : default_outline_color_frame;
        generateTexture->value = zox_generate_texture_trigger;
    }
} zox_declare_system(ElementActiveSystem)