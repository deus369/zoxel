// this will handle resume game & exit game & options
ecs_entity_t options_ui_prefab;

ecs_entity_t spawn_prefab_options_ui(ecs_world_t *world) {
    zox_prefab_child(prefab_window)
    zox_prefab_name("prefab_options_ui")
    // zox_add_tag(e, OptionsUI);
    options_ui_prefab = e;
    return e;
}

ecs_entity_t spawn_options_ui(ecs_world_t *world, const char *header_label, int2 position, int2 window_size, float2 anchor, unsigned char is_close_button) {
    return 0;
}