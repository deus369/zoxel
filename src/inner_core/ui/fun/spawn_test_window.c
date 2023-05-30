ecs_entity_t zoxel_window;

void spawn_zoxel_window(ecs_world_t *world) {
    if (zoxel_window != 0 && ecs_is_alive(world, zoxel_window)) {
        zoxel_log("Hiding zoxel window.\n");
        zox_delete(zoxel_window)
        zoxel_window = 0;
        return;
    }
    zoxel_log("Showing zoxel window.\n");
    int2 test_window_size = { 240, 320 };
    int2 test_window_position = { - test_window_size.x / 2, test_window_size.y / 2 };
    float2 test_window_anchor = { 1.0f, 0.0f };
    zoxel_window = spawn_window(world, "Console", test_window_position, test_window_size, test_window_anchor, main_canvas);
}