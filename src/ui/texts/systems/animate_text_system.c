void AnimateTextSystem(ecs_iter_t *it) {
    init_delta_time()
    zox_field_out(AnimateZext, animateZexts, 1)
    zox_field_out(ZextDirty, zextDirtys, 2)
    zox_field_out(ZextData, zextDatas, 3)
    unsigned char changed = 0;
    for (int i = 0; i < it->count; i++) {
        zox_field_o(AnimateZext, animateZexts, animateZext)
        animateZext->value -= delta_time;
        if (animateZext->value <= 0.0) {
            animateZext->value += zext_animation_speed;
            if (animateZext->value <= -zext_animation_speed) animateZext->value = 0;
            zox_field_o(ZextDirty, zextDirtys, zextDirty)
            if (zextDirty->value == 0) {
                zox_field_o(ZextData, zextDatas, zextData)
                const int index = rand() % zextData->length;
                zextData->value[index] = 1 + rand() % 52;
                changed = 1;
                zextDirty->value = 1;
#ifdef zoxel_debug_zext_updates
                zox_log("AnimateZext :: [%lu]\n", it->entities[i])
#endif
            }
        }
    }
    if (!changed) ecs_query_skip(it);
} zox_declare_system(AnimateTextSystem)
