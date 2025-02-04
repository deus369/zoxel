void test_action_bar(ecs_world_t *world) {
    int2 actionbar_size4 = (int2) { 420, 54 };
    int2 testSize2 = (int2) { 48, 48 };
    // actionbar - anchor actionbar to bottom
    ecs_entity_t action_bar = spawn_element_on_canvas(world, main_canvas, (int2) { 0, 10 + actionbar_size4.y / 2 }, actionbar_size4, (float2) { 0.5f, 0 });
    for (int i = 0; i < 5; i++)
    {
        // spawn element as child
    }
    spawn_element_on_canvas(world, action_bar, (int2) { 0, 10 + actionbar_size4.y / 2 }, testSize2, (float2) { 0.5f, 0 });
    spawn_element_on_canvas(world, action_bar, (int2) { - 3 * testSize2.x / 2, 10 + actionbar_size4.y / 2 }, testSize2, (float2) { 0.5f, 0 });
    spawn_element_on_canvas(world, action_bar, (int2) { 3 * testSize2.x / 2, 10 + actionbar_size4.y / 2 }, testSize2, (float2) { 0.5f, 0 });
    spawn_element_on_canvas(world, action_bar, (int2) { - 6 * testSize2.x / 2, 10 + actionbar_size4.y / 2 }, testSize2, (float2) { 0.5f, 0 });
    spawn_element_on_canvas(world, action_bar, (int2) { 6 * testSize2.x / 2, 10 + actionbar_size4.y / 2 }, testSize2, (float2) { 0.5f, 0 });
}

// used for testing the canvas scaling
void spawn_corner_uis(ecs_world_t *world) {
    const int2 testSize = { 32, 32 };
    spawn_element_on_canvas(world, main_canvas, (int2) { testSize.x / 2, testSize.y / 2 }, testSize, (float2) { 0, 0 });             // bottom left
    spawn_element_on_canvas(world, main_canvas, (int2) { - testSize.x / 2, testSize.y / 2 }, testSize, (float2) { 1.0f, 0.0 });      // bottom right
    spawn_element_on_canvas(world, main_canvas, (int2) { testSize.x / 2, - testSize.y / 2 }, testSize, (float2) { 0, 1.0f });        // top left
    spawn_element_on_canvas(world, main_canvas, (int2) { - testSize.x / 2, - testSize.y / 2 }, testSize, (float2) { 1.0f, 1.0f});
    zox_log("Spawned 4 corner ui elements.\n")    // top right
}

void spawn_test_uis(ecs_world_t *world) {
    spawn_corner_uis(world);
    // crosshair
    // spawn_element_on_canvas(world, canvas, (int2) { 0, 0 }, (int2) { 32, 32 }, (float2) { 0.5f, 0.5f });
    // test ui
    // test_action_bar(world);
    // spawn_element_on_canvas(world, canvas, (int2) { screenDimensions.x / 2, screenDimensions.y / 2 }, testSize);   // crosshair
    // spawn_zext(world, (int2) { 0, 0}, (float2) { 0.5f, 0.5f }, "Hello World.");
    // spawn_zext(world, (int2) { 0, - 8}, (float2) { 0.5f, 1.0f }, "abcdefghijklmnopqrstuvwxyz");
    // spawn_zext(world, (int2) { 0, actionbar_size4.y + 48}, (float2) { 0.5f, 0.0f }, "greetings minion");
}

void test_ui_pixel_positions(ecs_world_t *world) {
    // test horizontal by spawning one per bar
    int width_division = 2; // 16;
    int height_division = 32; // 16;
    int bar_width = viewport_dimensions.x / width_division; // 64;
    int bar_height = viewport_dimensions.y / height_division; // 64;
    int width_tests = 1 + viewport_dimensions.x / bar_width;
    int height_tests = 1 + viewport_dimensions.y / bar_height;
    for (int i = 0; i < height_tests; i++)
    {
        for (int j = 0; j < width_tests; j++)
        {
            spawn_element_on_canvas(world, main_canvas,
                (int2) { j * bar_width + bar_width / 2, i * bar_height + bar_height / 2 },
                (int2) { bar_width, bar_height }, (float2) { 0, 0 });
        }
    }
}
