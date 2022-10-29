//! Resets EntityDirty after one frame.
void AnimateNoiseSystem(ecs_iter_t *it)
{
    const double timePerUpdate = 0.25;
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
            animateTexture->value += timePerUpdate;
            GenerateTexture *generateTexture = &generateTextures[i];
            if (generateTexture->value == 0)
            {
                generateTexture->value = 1;
                changed = true;
                // printf("AnimateNoiseSystem Updating!\n");
            }
        }
    }
    if (!changed)
    {
        ecs_query_skip(it);
    }
}
ECS_SYSTEM_DECLARE(AnimateNoiseSystem);