ecs_entity_t prefab_virtual_joystick;
ecs_entity_t virtual_joystick;  // reference for now

ecs_entity_t spawn_prefab_virtual_joystick(ecs_world_t *world) {
    ecs_defer_begin(world);
    zox_prefab()
    zox_prefab_name("prefab_virtual_joystick")
    zox_add_tag(e, Button)
    zox_add_tag(e, FrameTexture)
    zox_set(e, FrameCorner, { 2 })
    zox_set(e, OutlineThickness, { 2 })
    zox_set(e, Color, { virtual_joystick_color })
    zox_set(e, Children, { 0, NULL })
    add_ui_plus_components(world, e);
    ecs_defer_end(world);
    prefab_virtual_joystick = e;
    #ifdef zoxel_debug_prefabs
        zoxel_log("spawn_prefab virtual_joystick [%lu].\n", (long int) (e));
    #endif
    return e;
}

ecs_entity_t spawn_virtual_joystick(ecs_world_t *world, int2 position) {
    int2 pixel_size = virtual_joystick_size;
    fix_for_screen_size(&pixel_size, screen_dimensions);
    float2 anchor = float2_zero;
    const unsigned char layer = 4;
    int2 canvas_size = ecs_get(world, main_canvas, PixelSize)->value;
    zox_instance(prefab_virtual_joystick)
    zox_name("virtual_joystick")
    float2 position2D = initialize_ui_components(world, e, main_canvas, position, pixel_size, anchor, 0, canvas_size);
    Children *children = ecs_get_mut(world, e, Children);
    initialize_memory_component(children, ecs_entity_t, 1)
    children->value[0] = spawn_virtual_joystick_pointer(world, e, (layer + 1), (int2) { 0, 0 }, (float2) { 0.5f, 0.5f }, position2D, pixel_size, canvas_size);
    ecs_modified(world, e, Children);
    virtual_joystick = e;
    #ifdef zoxel_debug_spawns
        zoxel_log("Spawned virtual_joystick [%lu]\n", (long int) e);
    #endif
    return e;
}