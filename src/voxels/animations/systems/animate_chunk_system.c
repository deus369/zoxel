void AnimateChunkSystem(ecs_iter_t *it) {
    return;
    double current_time = zox_current_time;
    AnimateChunk *animateChunks = ecs_field(it, AnimateChunk, 1);
    GenerateChunk *generateChunks = ecs_field(it, GenerateChunk, 2);
    unsigned char changed = 0;
    for (int i = 0; i < it->count; i++) {
        AnimateChunk *animateChunk = &animateChunks[i];
        if (current_time - animateChunk->value >= animating_chunk_speed) {
            animateChunk->value += animating_chunk_speed;
            GenerateChunk *generateChunk = &generateChunks[i];
            if (generateChunk->value == 0) {
                generateChunk->value = 1;
                changed = 1;
            }
        }
    }
    if (!changed) ecs_query_skip(it);
}
zox_declare_system(AnimateChunkSystem)
