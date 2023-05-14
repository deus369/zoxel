void AnimateChunkSystem(ecs_iter_t *it) {
    double current_time = zox_current_time;
    // double delta_time = zox_delta_time;
    AnimateChunk *animateChunks = ecs_field(it, AnimateChunk, 1);
    GenerateChunk *generateChunks = ecs_field(it, GenerateChunk, 2);
    unsigned char changed = 0;
    for (int i = 0; i < it->count; i++) {
        AnimateChunk *animateChunk = &animateChunks[i];
        //animateChunk->value -= delta_time;
        // zoxel_log(" > animating chunk [%lu] at [%f :: %f]\n", it->entities[i], (float) animateChunk->value, (float) delta_time);
        //if (animateChunk->value <= 0.0) {
        // animateChunk->value += animating_chunk_speed;
        if (current_time - animateChunk->value >= animating_chunk_speed) {
            animateChunk->value += animating_chunk_speed;
            // animateChunk->value = current_time;
            /*if (animateChunk->value <= -animating_chunk_speed) {
                animateChunk->value = 0;
            }*/
            GenerateChunk *generateChunk = &generateChunks[i];
            if (generateChunk->value == 0) {
                generateChunk->value = 1;
                changed = 1;
                // zoxel_log(" > animating chunk [%lu] at [%f]\n", it->entities[i], (float) zox_current_time);
            }
        }
    }
    if (!changed) {
        ecs_query_skip(it);
    }
}
zox_declare_system(AnimateChunkSystem)