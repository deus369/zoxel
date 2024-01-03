//! Testing, spawn more!
void spawn_many_characters2D(ecs_world_t *world) {
    for (int i = 0; i < spawn_characters2D_count; i++) {
        spawn_character2D(world, character2D_prefab, (float2) {
            -0.5f + (rand() % 100) * 0.2f, -0.5f + (rand() % 100) * 0.2f });
    }
}
