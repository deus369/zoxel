//! Testing, spawn more!
void spawn_many_characters2D(ecs_world_t *world, ecs_entity_t prefab) {
    for (int i = 0; i < spawn_characters2D_count; i++) {
        spawn_character2D(world, prefab, (float2) {
            -0.5f + (rand() % 100) * 0.2f, -0.5f + (rand() % 100) * 0.2f });
    }
}
