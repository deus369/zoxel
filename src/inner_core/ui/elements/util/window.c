//! Spawns a window element.
ecs_entity_t spawn_window(ecs_world_t *world, const char *header_label, int2 position, int2 pixel_size, float2 anchor, ecs_entity_t canvas) {
    int font_size = 28;
    int header_margins = 4;
    ecs_defer_begin(world);
    ecs_entity_t e = ecs_new_w_pair(world, EcsIsA, window_prefab);
    set_unique_entity_name(world, e, "window");
    float2 position2D = initialize_ui_components(world, e, canvas, position, pixel_size, anchor, 0, ecs_get(world, canvas, PixelSize)->value);
    Children children = { };
    initialize_memory_component_non_pointer(children, ecs_entity_t, 1);
    children.value[0] = spawn_header(world, e, (int2) { 0, - font_size / 2 - header_margins / 2 }, (int2) { pixel_size.x, font_size + header_margins},
        (float2) { 0.5f, 1.0f }, header_label, font_size, header_margins, 1, position2D, pixel_size, 1);
    ecs_set(world, e, Children, { children.length, children.value });
    ecs_defer_end(world);
    #ifdef zoxel_debug_spawns
        zoxel_log("Spawned window [%lu]\n", (long int) e);
    #endif
    return e;
}