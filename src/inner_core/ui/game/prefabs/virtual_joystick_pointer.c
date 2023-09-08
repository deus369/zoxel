ecs_entity_t prefab_virtual_joystick_pointer;
ecs_entity_t virtual_joystick_pointer;  // reference for now

ecs_entity_t spawn_prefab_virtual_joystick_pointer(ecs_world_t *world) {
    ecs_defer_begin(world);
    zox_prefab()
    zox_name("prefab_virtual_joystick_pointer")
    zox_add_tag(e, Button)
    zox_add_tag(e, FrameTexture)
    zox_set(e, FrameCorner, { 4 })
    zox_set(e, OutlineThickness, { 4 })
    zox_set(e, Color, { virtual_joystick_pointer_color })
    add_ui_plus_components(world, e);
    ecs_defer_end(world);
    prefab_virtual_joystick_pointer = e;
    #ifdef zoxel_debug_prefabs
        zoxel_log("spawn_prefab virtual_joystick_pointer [%lu].\n", (long int) (e));
    #endif
    return e;
}

ecs_entity_t spawn_virtual_joystick_pointer(ecs_world_t *world, ecs_entity_t parent, unsigned char layer, int2 position, float2 anchor, float2 parent_position2D, int2 parent_pixel_size, int2 canvas_size) {
    int2 pixel_size = virtual_joystick_pointer_size;
    fix_for_screen_size(&pixel_size, screen_dimensions);
    zox_instance(prefab_virtual_joystick_pointer)
    zox_name("virtual_joystick_pointer")
    initialize_ui_components_2(world, e, parent, position, pixel_size, anchor, layer, parent_position2D, parent_pixel_size, canvas_size);
    virtual_joystick_pointer = e;
    #ifdef zoxel_debug_spawns
        zoxel_log("Spawned virtual_joystick_pointer [%lu]\n", (long int) e);
    #endif
    return e;
}