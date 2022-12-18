//! Every noise_animation_speed it makes the texture update.
void AnimateTextSystem(ecs_iter_t *it)
{
    // printf("AnimateZext: %i\n", it->count);
    double deltaTime = it->delta_time;
    AnimateZext *animateZexts = ecs_field(it, AnimateZext, 1);
    ZextDirty *zextDirtys = ecs_field(it, ZextDirty, 2);
    ZextData *zextDatas = ecs_field(it, ZextData, 3);
    bool changed = false;   //! Skip changes if texture isn't updated.
    for (int i = 0; i < it->count; i++)
    {
        AnimateZext *animateZext = &animateZexts[i];
        animateZext->value -= deltaTime;
        if (animateZext->value <= 0.0)
        {
            animateZext->value += zext_animation_speed;
            if (animateZext->value <= -zext_animation_speed)
            {
                animateZext->value = 0;
            }
            ZextDirty *zextDirty = &zextDirtys[i];
            if (zextDirty->value == 0)
            {
                zextDirty->value = 1;
                #ifdef zoxel_debug_zext_updates
                printf("AnimateZext :: [%lu]\n", (long int) it->entities[i]);
                #endif
                // update text to new thing
                ZextData *zextData = &zextDatas[i];
                int index = rand() % zextData->length;
                zextData->value[index] = 1 + rand() % 52;
                /*if (zextData->value[index] > 52)
                {
                    zextData->value[index] = 0;
                }*/
                changed = true;
                // printf("AnimateNoiseSystem, GenerateTexture Triggered: [%lu] on index [%i]\n", (long int)(it->entities[i]), i);
            }
        }
    }
    if (!changed)
    {
        ecs_query_skip(it);
    }
}
ECS_SYSTEM_DECLARE(AnimateTextSystem);