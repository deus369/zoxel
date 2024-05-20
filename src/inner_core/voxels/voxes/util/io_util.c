// I/O
void initialize_voxes(ecs_world_t *world) {
    load_files_voxes();
}

void dispose_voxes(ecs_world_t *world) {
    dispose_files_voxes(world);
}
