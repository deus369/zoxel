zox_declare_tag(App)
zox_component_byte(WindowFullscreen)
zox_component_int2(WindowSize)
zox_component_int2(WindowPosition)
zox_component_int2(WindowSizeRestore)

void define_components_apps(ecs_world_t *world) {
    zox_define_tag(App)
    zox_define_component_byte(WindowFullscreen)
    zox_define_component_int2(WindowSize)
    zox_define_component_int2(WindowPosition)
    zox_define_component_int2(WindowSizeRestore)
#ifdef zox_include_vulkan
    zox_define_component(VulkanSurface)
#endif
}