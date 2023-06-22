ECS_DTOR(SDLWindow, ptr, {
    if (ptr->value != 0) SDL_DestroyWindow(ptr->value);
})

ECS_DTOR(Renderer, ptr, {
    if (ptr->value != 0) SDL_DestroyRenderer(ptr->value);
})

ECS_DTOR(Context, ptr, {
    if (ptr->value != 0) SDL_GL_DeleteContext(ptr->value);
})

#ifdef zoxel_include_vulkan
    ECS_DTOR(VulkanSurface, ptr, {
        if (ptr->value != 0) vkDestroySurfaceKHR(*main_vulkan_instance, *ptr->value, NULL);
    })
#endif