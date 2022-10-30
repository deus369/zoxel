//! Every noiseAnimationSpeed it makes the texture update.
void AnimateNoiseSystem(ecs_iter_t *it)
{
    double deltaTime = it->delta_time;
    AnimateTexture *animateTextures = ecs_field(it, AnimateTexture, 1);
    GenerateTexture *generateTextures = ecs_field(it, GenerateTexture, 2);
    bool changed = false;   //! Skip changes if texture isn't updated.
    for (int i = 0; i < it->count; i++)
    {
        AnimateTexture *animateTexture = &animateTextures[i];
        animateTexture->value -= deltaTime;
        if (animateTexture->value <= 0.0)
        {
            animateTexture->value += noiseAnimationSpeed;
            if (animateTexture->value <= -noiseAnimationSpeed)
            {
                animateTexture->value = 0;
            }
            GenerateTexture *generateTexture = &generateTextures[i];
            if (generateTexture->value == 0)
            {
                generateTexture->value = 1;
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
ECS_SYSTEM_DECLARE(AnimateNoiseSystem);