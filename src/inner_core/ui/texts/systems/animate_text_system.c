void AnimateTextSystem(ecs_iter_t *it) {
    double deltaTime = it->delta_time;
    AnimateZext *animateZexts = ecs_field(it, AnimateZext, 1);
    ZextDirty *zextDirtys = ecs_field(it, ZextDirty, 2);
    ZextData *zextDatas = ecs_field(it, ZextData, 3);
    unsigned char changed = 0;
    for (int i = 0; i < it->count; i++) {
        AnimateZext *animateZext = &animateZexts[i];
        animateZext->value -= deltaTime;
        if (animateZext->value <= 0.0) {
            animateZext->value += zext_animation_speed;
            if (animateZext->value <= -zext_animation_speed) animateZext->value = 0;
            ZextDirty *zextDirty = &zextDirtys[i];
            if (zextDirty->value == 0) {
                zextDirty->value = 1;
                #ifdef zoxel_debug_zext_updates
                    printf("AnimateZext :: [%lu]\n", (long int) it->entities[i]);
                #endif
                ZextData *zextData = &zextDatas[i];
                int index = rand() % zextData->length;
                zextData->value[index] = 1 + rand() % 52;
                changed = 1;
                // printf("AnimateNoiseSystem, GenerateTexture Triggered: [%lu] on index [%i]\n", (long int)(it->entities[i]), i);
            }
        }
    }
    if (!changed) ecs_query_skip(it);
} zox_declare_system(AnimateTextSystem)