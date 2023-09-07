ecs_entity_t prefab_virtual_joystick;
ecs_entity_t virtual_joystick;  // reference for now

ecs_entity_t spawn_prefab_virtual_joystick(ecs_world_t *world) {
    ecs_defer_begin(world);
    zox_prefab()
    zox_name("prefab_virtual_joystick")
    zox_add_tag(e, Button)
    zox_add_tag(e, FrameTexture)
    zox_set(e, FrameCorner, { 2 })
    zox_set(e, OutlineThickness, { 2 })
    zox_set(e, Color, { virtual_joystick_color })
    zox_set(e, Children, { 0, NULL })
    add_ui_plus_components(world, e);
    // zox_add_tag(e, Selectable)
    // zox_add_tag(e, Clickable)
    // zox_set(e, ClickEvent, { NULL })
    // zox_set(e, SelectableState, { 0 })
    // zox_set(e, ClickableState, { 0 })
    ecs_defer_end(world);
    prefab_virtual_joystick = e;
    #ifdef zoxel_debug_prefabs
        zoxel_log("spawn_prefab virtual_joystick [%lu].\n", (long int) (e));
    #endif
    return e;
}

ecs_entity_t spawn_virtual_joystick(ecs_world_t *world, int2 position) {
    int2 pixel_size = virtual_joystick_size;
    float2 anchor = float2_zero;
    ecs_entity_t parent = 0;
    float2 parent_position2D = float2_zero;
    int2 parent_pixel_size = int2_zero;
    unsigned char layer = 4;
    int2 canvas_size = ecs_get(world, main_canvas, PixelSize)->value;
    // ecs_entity_t parent, int2 position, int2 padding, float2 anchor, const char* text, int font_size, unsigned char layer, float2 parent_position2D, int2 parent_pixel_size, int2 canvas_size) {
    // int2 zext_size = (int2) { font_size * strlen(text), font_size };
    zox_instance(prefab_virtual_joystick)
    zox_name("virtual_joystick")
    float2 position2D = initialize_ui_components(world, e, main_canvas, position, pixel_size, anchor, 0, canvas_size);
    // float2 position2D = initialize_ui_components_2(world, e, parent, position, virtual_joystick_size, anchor, layer, parent_position2D, parent_pixel_size, canvas_size);
    Children children = { };
    initialize_memory_component_non_pointer(children, ecs_entity_t, 1);
    children.value[0] = spawn_virtual_joystick_pointer(world, e,
        (layer + 1), (int2) { 0, 0 }, (float2) { 0.5f, 0.5f }, position2D, pixel_size, canvas_size);
    // unsigned char layer, int2 position, float2 anchor, float2 parent_position2D, int2 parent_pixel_size, int2 canvas_size
    zox_set_only(e, Children, { children.length, children.value })
    virtual_joystick = e;
    #ifdef zoxel_debug_spawns
        zoxel_log("Spawned virtual_joystick [%lu]\n", (long int) e);
    #endif
    return e;
}