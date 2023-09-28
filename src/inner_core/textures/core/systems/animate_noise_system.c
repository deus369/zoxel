void AnimateNoiseSystem(ecs_iter_t *it) {
    return;
    double delta_time = zox_delta_time;
    // double delta_time = it->delta_time;
    AnimateTexture *animateTextures = ecs_field(it, AnimateTexture, 1);
    GenerateTexture *generateTextures = ecs_field(it, GenerateTexture, 2);
    unsigned char changed = 0;
    for (int i = 0; i < it->count; i++) {
        AnimateTexture *animateTexture = &animateTextures[i];
        animateTexture->value -= delta_time;
        if (animateTexture->value <= 0.0) {
            animateTexture->value += noise_animation_speed;
            if (animateTexture->value <= -noise_animation_speed) animateTexture->value = 0;
            GenerateTexture *generateTexture = &generateTextures[i];
            if (generateTexture->value == 0) {
                generateTexture->value = 1;
                changed = 1;
                // printf("AnimateNoiseSystem, GenerateTexture Triggered: [%lu] on index [%i]\n", (long int)(it->entities[i]), i);
            }
        }
    }
    if (!changed) ecs_query_skip(it);
} zox_declare_system(AnimateNoiseSystem)