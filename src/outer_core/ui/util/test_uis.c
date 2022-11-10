void spawn_test_uis(ecs_world_t *world)
{
    spawn_canvas(world, screenDimensions);
    // test ui
    int2 testSize = { 32, 32 };
    int2 actionbar_size4 = (int2) { 420, 54 };
    int2 testSize2 = (int2) { 48, 48 };
    // spawn_element(world, (int2) { screenDimensions.x / 2, screenDimensions.y / 2 }, testSize);   // crosshair
    spawn_element(world, (int2) { testSize.x / 2, testSize.y / 2 }, testSize, (float2) { });                  // bottom left
    spawn_element(world, (int2) { - testSize.x / 2, testSize.y / 2 }, testSize, (float2) { 1.0f, 0.0 });      // bottom right
    spawn_element(world, (int2) { testSize.x / 2, - testSize.y / 2 }, testSize, (float2) { 0, 1.0f });        // top left
    spawn_element(world, (int2) { - testSize.x / 2, - testSize.y / 2 }, testSize, (float2) { 1.0f, 1.0f});    // top right
    // actionbar - anchor actionbar to bottom
    spawn_element(world, (int2) { 0, 10 + actionbar_size4.y / 2 }, actionbar_size4, (float2) { 0.5f, 0 });
    //! \todo Spawn these as children~
    //! \todo Destroy when destroy actionbar
    //! \todo Transform hierarchy, child positioning
    spawn_element(world, (int2) { 0, 10 + actionbar_size4.y / 2 }, testSize2, (float2) { 0.5f, 0 });
    spawn_element(world, (int2) { - 3 * testSize2.x / 2, 10 + actionbar_size4.y / 2 }, testSize2, (float2) { 0.5f, 0 });
    spawn_element(world, (int2) { 3 * testSize2.x / 2, 10 + actionbar_size4.y / 2 }, testSize2, (float2) { 0.5f, 0 });
    spawn_element(world, (int2) { - 6 * testSize2.x / 2, 10 + actionbar_size4.y / 2 }, testSize2, (float2) { 0.5f, 0 });
    spawn_element(world, (int2) { 6 * testSize2.x / 2, 10 + actionbar_size4.y / 2 }, testSize2, (float2) { 0.5f, 0 });
    // test horizontal by spawning one per bar
    /*int width_division = 2; // 16;
    int height_division = 32; // 16;
    int bar_width = screenDimensions.x / width_division; // 64;
    int bar_height = screenDimensions.y / height_division; // 64;
    int width_tests = 1 + screenDimensions.x / bar_width;
    int height_tests = 1 + screenDimensions.y / bar_height;
    for (int i = 0; i < height_tests; i++)
    {
        for (int j = 0; j < width_tests; j++)
        {
            spawn_element(world,
                (int2) { j * bar_width + bar_width / 2, i * bar_height + bar_height / 2 },
                (int2) { bar_width, bar_height });
        }
    }*/
}