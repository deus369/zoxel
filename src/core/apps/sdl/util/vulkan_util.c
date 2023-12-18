#ifdef zox_include_vulkan

// todo:
//  1 Create Swap Chain
//  2 Create Graphics Pipeline
//  3 Finish this list

VkInstance* main_vulkan_instance;
VkSurfaceKHR* main_vulkan_context;
VkDevice vk_device;
VkCommandBuffer vk_command_buffer;
VkRenderPass vk_render_pass;
VkFramebuffer vk_frame_buffer;
VkExtent2D vk_swap_chain_event;

zox_component(VulkanSurface, VkSurfaceKHR*)
// zox_component(VulkanInstance, VkInstance*)
ECS_DTOR(VulkanSurface, ptr, { if (ptr->value != 0) vkDestroySurfaceKHR(*main_vulkan_instance, *ptr->value, NULL); })

void dispose_vulkan_instance() {
    if (*main_vulkan_instance != VK_NULL_HANDLE) {
        zox_logg(" > destroying [main_vulkan_instance]\n")
        vkDestroyInstance(*main_vulkan_instance, NULL);
        *main_vulkan_instance = VK_NULL_HANDLE;
    }
}

void vulkan_clear_viewport(float3 clear_color) {

    return; // have to create the other parts of vulkan first

    // Convert the color structure to VkClearValue
    VkClearValue clearColor = { { clear_color.x, clear_color.y, clear_color.z, 1 } };

    // Define the render pass begin info
    VkRenderPassBeginInfo renderPassInfo = {};
    renderPassInfo.sType = VK_STRUCTURE_TYPE_RENDER_PASS_BEGIN_INFO;
    renderPassInfo.renderPass = vk_render_pass;
    renderPassInfo.framebuffer = vk_frame_buffer;
    renderPassInfo.renderArea.offset = (VkOffset2D) { 0, 0 };
    renderPassInfo.renderArea.extent = vk_swap_chain_event;
    renderPassInfo.clearValueCount = 1;
    renderPassInfo.pClearValues = &clearColor;
    // Begin the render pass
    vkCmdBeginRenderPass(vk_command_buffer, &renderPassInfo, VK_SUBPASS_CONTENTS_INLINE);
    // Here, the viewport is cleared with the specified color

    // End the render pass
    vkCmdEndRenderPass(vk_command_buffer);
}

const char* vulkan_result_to_string(VkResult result) {
    switch (result) {
        case VK_SUCCESS:
            return "VK_SUCCESS";
        case VK_NOT_READY:
            return "VK_NOT_READY";
        case VK_TIMEOUT:
            return "VK_TIMEOUT";
        case VK_EVENT_SET:
            return "VK_EVENT_SET";
        case VK_EVENT_RESET:
            return "VK_EVENT_RESET";
        case VK_INCOMPLETE:
            return "VK_INCOMPLETE";
        case VK_ERROR_OUT_OF_HOST_MEMORY:
            return "VK_ERROR_OUT_OF_HOST_MEMORY";
        case VK_ERROR_OUT_OF_DEVICE_MEMORY:
            return "VK_ERROR_OUT_OF_DEVICE_MEMORY";
        case VK_ERROR_INITIALIZATION_FAILED:
            return "VK_ERROR_INITIALIZATION_FAILED";
        // Handle other specific error codes as needed
        default:
            return "Unknown VkResult";
    }
}

VkSurfaceKHR create_vulkan_surface( SDL_Window* window, VkInstance instance) {
    VkSurfaceKHR surface;
    if (!SDL_Vulkan_CreateSurface(window, instance, &surface)) {
        zoxel_log(" ! failed to create vulkan surface [%s]\n", SDL_GetError());
        return VK_NULL_HANDLE;
    }
    return surface;
}

ecs_entity_t spawn_app_vulkan(ecs_world_t *world, SDL_Window* window, VkSurfaceKHR* surface) {
    zox_instance(prefab_app)
    zox_set(e, SDLWindow, { window })
    zox_set(e, VulkanSurface, { surface })
    main_app = e;
    return e;
}

unsigned char create_main_window_vulkan(ecs_world_t *world, SDL_Window* window) {
    zox_logg(" > creating vulkan surface\n")
    if (window == NULL) {
        zox_logg(" > window is null, cannot create vulkan surface\n")
        return EXIT_FAILURE;
    }
    unsigned int extensionCount;
    if (!SDL_Vulkan_GetInstanceExtensions(NULL, &extensionCount, NULL)) {
        zox_logg(" ! vulkan is not supporoted (SDL_Vulkan_GetInstanceExtensions failed)\n")
        return EXIT_FAILURE;
    }
    if (!SDL_Vulkan_GetInstanceExtensions(window, &extensionCount, NULL)) {
        const char* error = SDL_GetError();
        if (error && *error != '\0') {
            zox_log(" ! SDL_Vulkan_GetInstanceExtensions failed: %s\n", error);
        } else {
            zox_logg(" ! SDL_Vulkan_GetInstanceExtensions failed: no sdl error\n");
        }
        return EXIT_FAILURE;
    }
    const char** extensions = malloc(extensionCount * sizeof(const char*));
    if (!SDL_Vulkan_GetInstanceExtensions(window, &extensionCount, extensions)) {
        zox_logg(" ! SDL_Vulkan_GetInstanceExtensions 2 failed\n")
        return EXIT_FAILURE;
    }
    zox_log(" > vulkan instance extensions [%i]\n", extensionCount)
    for (unsigned int i = 0; i < extensionCount; i++) zox_log("     [%i]: %s\n", i, extensions[i])
    VkInstanceCreateInfo instanceCreateInfo = {
        VK_STRUCTURE_TYPE_INSTANCE_CREATE_INFO, // sType
        NULL,                                   // pNext
        0,                                      // flags
        NULL,                                   // pApplicationInfo
        0,                                      // enabledLayerCount
        NULL,                                   // ppEnabledLayerNames
        extensionCount,                         // enabledExtensionCount
        extensions,                             // ppEnabledExtensionNames
    };
    VkInstance instance;
    VkResult result = vkCreateInstance(&instanceCreateInfo, NULL, &instance);
    free(extensions);
    if (result != VK_SUCCESS) {
        zoxel_log(" ! failed to create vulkan instance [%s]\n", vulkan_result_to_string(result));
        return EXIT_FAILURE;
    }
    VkSurfaceKHR surface = create_vulkan_surface(window, instance);
    if (surface == NULL) {
        zoxel_log(" ! failed to create VkSurfaceKHR\n");
        return EXIT_FAILURE;
    }
    spawn_app_vulkan(world, window, &surface);
    main_vulkan_context = &surface;
    main_vulkan_instance = &instance;
    zox_logg(" + success creating vulkan\n")
    return EXIT_SUCCESS;
}

#endif

// VkInstanceCreateInfo instanceCreateInfo = { };
// instanceCreateInfo.sType = VK_STRUCTURE_TYPE_INSTANCE_CREATE_INFO;

    // Initialize Wayland display
    /*struct wl_display *display = wl_display_connect(NULL);
    if (display == NULL) {
        return VK_NULL_HANDLE;
    }

    // Initialize Wayland surface
    struct wl_surface *surface = wl_compositor_create_surface(compositor);
    if (surface == NULL) {
        return VK_NULL_HANDLE;
    }
    PFN_vkGetInstanceProcAddr vkGetInstanceProcAddr = wl_display_get_vk_proc_addr(display);
    if (!vkGetInstanceProcAddr) {
        return VK_NULL_HANDLE;
    }

    PFN_vkCreateWaylandSurfaceKHR vkCreateWaylandSurfaceKHR =
        (PFN_vkCreateWaylandSurfaceKHR)vkGetInstanceProcAddr(instance, "vkCreateWaylandSurfaceKHR");
    if (!vkCreateWaylandSurfaceKHR) {
        return VK_NULL_HANDLE;
    }

    VkWaylandSurfaceCreateInfoKHR surfaceCreateInfo = {
        .sType = VK_STRUCTURE_TYPE_WAYLAND_SURFACE_CREATE_INFO_KHR,
        .pNext = NULL,
        .flags = 0,
        .display = display,
        .surface = surface
    };

    VkSurfaceKHR vkSurface;
    VkResult result = vkCreateWaylandSurfaceKHR(instance, &surfaceCreateInfo, NULL, &vkSurface);
    if (result != VK_SUCCESS) {
        return VK_NULL_HANDLE;
    }
    return vkSurface;*/

    /*VkSurfaceKHR surface;
    const char* waylandDisplay = getenv("WAYLAND_DISPLAY");
    if (waylandDisplay != NULL) {
        // Running on Wayland
        VkWaylandSurfaceCreateInfoKHR createInfo = {
            .sType = VK_STRUCTURE_TYPE_WAYLAND_SURFACE_CREATE_INFO_KHR,
            .pNext = NULL,
            .flags = 0,
            .display = display,
            .surface = wl_compositor_create_surface(wl_display_get_compositor(display), NULL)
        };
        if (vkCreateWaylandSurfaceKHR(instance, &createInfo, NULL, &surface) != VK_SUCCESS) {
            fprintf(stderr, "Failed to create Vulkan surface\n");
            return VK_NULL_HANDLE;
        }
    } else {
        // Running on X11
        return VK_NULL_HANDLE;
    }*/
    /*VkWaylandSurfaceCreateInfoKHR createInfo = {
        .sType = VK_STRUCTURE_TYPE_WAYLAND_SURFACE_CREATE_INFO_KHR,
        .pNext = NULL,
        .flags = 0,
        .display = display,
        .surface = SDL_waylandCreateSurface(window)
    };
    if (vkCreateWaylandSurfaceKHR(instance, &createInfo, NULL, &surface) != VK_SUCCESS) {
        fprintf(stderr, "Failed to create Vulkan surface\n");
        return VK_NULL_HANDLE;
    }*/
    // wl_display_disconnect(display);
