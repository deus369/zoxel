zox_tag(App);
zoxc_byte(WindowSizeDirty);
zoxc_byte(WindowFullscreen);
zoxc_byte(WindowMaximized);
zoxc_byte(WindowMonitor);
zoxc_int2(WindowSize);
zoxc_int2(WindowPosition);
zoxc_int2(WindowSizeRestore);
zoxc_int2(WindowPositionRestore);
zoxc_entity(AppLink);

void define_components_apps(ecs_world_t *world) {
    zox_define_tag(App);
    zox_define_component_byte(WindowSizeDirty);
    zox_define_component_byte(WindowFullscreen);
    zox_define_component_byte(WindowMaximized);
    zox_define_component_byte(WindowMonitor);
    zox_define_component_int2(WindowSize);
    zox_define_component_int2(WindowPosition);
    zox_define_component_int2(WindowSizeRestore);
    zox_define_component_int2(WindowPositionRestore);
    zox_define_component_entity(AppLink);
#ifdef zox_vulkan
    zox_define_component(VulkanSurface);
#endif
}