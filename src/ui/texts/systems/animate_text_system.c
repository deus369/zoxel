void AnimateTextSystem(iter *it) {
    init_delta_time()
    zox_sys_begin()
    zox_sys_out(AnimateZext)
    zox_sys_out(ZextDirty)
    zox_sys_out(TextData)
    byte changed = 0;
    for (int i = 0; i < it->count; i++) {
        zox_sys_o(AnimateZext, animateZext)
        zox_sys_o(ZextDirty, zextDirty)
        zox_sys_o(TextData, textData)
        animateZext->value -= delta_time;
        if (animateZext->value <= 0.0) {
            animateZext->value += zext_animation_speed;
            if (animateZext->value <= -zext_animation_speed) animateZext->value = 0;
            if (zextDirty->value == 0) {
                const int index = rand() % textData->length;
                textData->value[index] = 1 + rand() % 52;
                changed = 1;
                zextDirty->value = 1;
#ifdef zoxel_debug_zext_updates
                zox_log("AnimateZext :: [%lu]\n", it->entities[i])
#endif
            }
        }
    }
    if (!changed) zox_skip()
} zox_declare_system(AnimateTextSystem)
