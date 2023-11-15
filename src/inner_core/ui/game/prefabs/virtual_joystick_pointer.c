ecs_entity_t prefab_virtual_joystick_pointer;
ecs_entity_t virtual_joystick_pointer;  // reference for now

ecs_entity_t spawn_prefab_virtual_joystick_pointer(ecs_world_t *world) {
    zox_prefab()
    zox_prefab_name("prefab_virtual_joystick_pointer")
    zox_add_tag(e, Button)
    zox_add_tag(e, FrameTexture)
    zox_prefab_set(e, FrameCorner, { 4 })
    zox_prefab_set(e, OutlineThickness, { 4 })
    zox_prefab_set(e, Color, { virtual_joystick_pointer_color })
    add_ui_plus_components(world, e);
    prefab_virtual_joystick_pointer = e;
    #ifdef zoxel_debug_prefabs
        zox_log("   > spawn_prefab virtual_joystick_pointer [%lu].\n", e)
    #endif
    return e;
}

ecs_entity_t spawn_virtual_joystick_pointer(ecs_world_t *world, ecs_entity_t parent, ecs_entity_t canvas, unsigned char layer, int2 pixel_position, float2 anchor, int2 parent_pixel_position_global, int2 parent_pixel_size, int2 canvas_size) {
    int2 pixel_size = virtual_joystick_pointer_size;
    fix_for_screen_size(&pixel_size, screen_dimensions);
    zox_instance(prefab_virtual_joystick_pointer)
    zox_name("virtual_joystick_pointer")
    int2 pixel_position_global = get_element_pixel_position_global(parent_pixel_position_global, parent_pixel_size, pixel_position, anchor);
    float2 position2D = get_element_position(pixel_position_global, canvas_size);
    initialize_ui_components_3(world, e, parent, canvas, pixel_position, pixel_size, anchor, layer, position2D, pixel_position_global);
    virtual_joystick_pointer = e;
#ifdef zoxel_debug_spawns
    zox_log("   > spawned virtual_joystick_pointer [%lu]\n", e)
#endif
    return e;
}
