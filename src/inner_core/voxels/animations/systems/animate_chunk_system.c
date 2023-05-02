void AnimateChunkSystem(ecs_iter_t *it) {
    double deltaTime = it->delta_time;
    AnimateChunk *animateTextures = ecs_field(it, AnimateChunk, 1);
    GenerateChunk *generateChunks = ecs_field(it, GenerateChunk, 2);
    unsigned char changed = 0;
    for (int i = 0; i < it->count; i++) {
        AnimateChunk *animateChunk = &animateTextures[i];
        animateChunk->value -= deltaTime;
        if (animateChunk->value <= 0.0) {
            animateChunk->value += noiseChunkAnimateSpeed;
            if (animateChunk->value <= -noiseChunkAnimateSpeed) {
                animateChunk->value = 0;
            }
            GenerateChunk *generateChunk = &generateChunks[i];
            if (generateChunk->value == 0) {
                generateChunk->value = 1;
                changed = 1;
                // printf("AnimateNoiseSystem, GenerateChunk Triggered: [%lu] on index [%i]\n", (long int)(it->entities[i]), i);
            }
        }
    }
    if (!changed) {
        ecs_query_skip(it);
    }
}
zoxel_declare_system(AnimateChunkSystem)