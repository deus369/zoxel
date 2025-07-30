// sdl - vulkan load stuff
#ifdef zox_vulkan

// #define zox_debug_vulkan_core
// make VULKAN=1 && make run-vulkan
zox_component(VulkanSurface, VkSurfaceKHR*) // goes onto the sdl app

// from vulkan module:
extern VkSurfaceKHR create_vulkan_surface( SDL_Window* window, VkInstance instance);
extern byte create_vulkan_pipeline(ecs_world_t *world, VkInstance* vk_instance, VkSurfaceKHR* vk_surface);
extern VkInstance* vk_instance;
extern VkSurfaceKHR* vk_surface;

byte load_vulkan_library() {
    if (render_backend == zox_render_backend_vulkan) {
        if (SDL_Vulkan_LoadLibrary(NULL) != 0) {
            zox_log(" ! failed to load vulkan library [%s]\n", SDL_GetError())
            return EXIT_FAILURE;
        } else {
            zox_log(" + vulkan library loaded\n")
        }
    }
    return EXIT_SUCCESS;
}

ecs_entity_t spawn_app_vulkan(ecs_world_t *world, SDL_Window* window, VkSurfaceKHR* surface) {
    zox_instance(prefab_app)
    zox_set(e, SDLWindow, { window })
    zox_set(e, VulkanSurface, { surface })
    main_app = e;
    return e;
}

void zox_log_vulkan_args(const char *text, ...) {
#ifdef zox_debug_vulkan_core
    va_list args;
    va_start(args, text);
    zox_log(text, args)
    va_end(args);
#endif
}

void zox_log_vulkan_no_args(const char *text) {
#ifdef zox_debug_vulkan_core
    zox_log(text)
#endif
}

#define zox_log_vulkan(msg, ...) {\
    if (ARG_COUNT(__VA_ARGS__) == 0) {\
        zox_log_vulkan_no_args(msg);\
    } else {\
        zox_log_vulkan_args(msg, #__VA_ARGS__);\
    }\
}

ecs_entity_t spawn_main_window_vulkan(ecs_world_t *world, SDL_Window* window) {
    zox_log_vulkan(" > creating vulkan surface\n")
    if (window == NULL) {
        zox_log_vulkan(" > window is null, cannot create vulkan surface\n")
        return 0;
    }
    unsigned int extensionCount;
    if (!SDL_Vulkan_GetInstanceExtensions(NULL, &extensionCount, NULL)) {
        zox_log_vulkan(" ! vulkan is not supporoted (SDL_Vulkan_GetInstanceExtensions failed)\n")
        return 0;
    }
    if (!SDL_Vulkan_GetInstanceExtensions(window, &extensionCount, NULL)) {
        const char* error = SDL_GetError();
        if (error && *error != '\0') {
            zox_log_vulkan(" ! SDL_Vulkan_GetInstanceExtensions failed: %s\n", error);
        } else {
            zox_log_vulkan(" ! SDL_Vulkan_GetInstanceExtensions failed: no sdl error\n");
        }
        return 0;
    }
    const char** extensions = malloc(extensionCount * sizeof(const char*));
    if (!SDL_Vulkan_GetInstanceExtensions(window, &extensionCount, extensions)) {
        zox_log_vulkan(" ! SDL_Vulkan_GetInstanceExtensions 2 failed\n")
        return EXIT_FAILURE;
    }
    zox_log_vulkan(" > vulkan instance extensions [%i]\n", extensionCount)
    for (unsigned int i = 0; i < extensionCount; i++) zox_log_vulkan("     [%i]: %s\n", i, extensions[i])

    VkInstanceCreateInfo instanceCreateInfo = { };
    instanceCreateInfo.sType = VK_STRUCTURE_TYPE_INSTANCE_CREATE_INFO;
    instanceCreateInfo.enabledExtensionCount = extensionCount;
    instanceCreateInfo.ppEnabledExtensionNames = extensions;
    /*const char* validationLayers[] = { "VK_LAYER_KHRONOS_validation" };
    instanceCreateInfo.enabledLayerCount = 1;
    instanceCreateInfo.ppEnabledLayerNames = validationLayers;*/

    VkInstance instance;
    VkResult result = vkCreateInstance(&instanceCreateInfo, NULL, &instance);
    free(extensions);
    if (result != VK_SUCCESS) {
        zox_log_vulkan(" ! failed to create vulkan instance [%s]\n", vulkan_result_to_string(result))
        return EXIT_FAILURE;
    }

    VkSurfaceKHR surface = create_vulkan_surface(window, instance);
    if (surface == NULL) {
        zox_log_vulkan(" ! failed to create VkSurfaceKHR\n")
        return EXIT_FAILURE;
    }
    vk_instance = malloc(sizeof(VkInstance));
    vk_surface = malloc(sizeof(VkSurfaceKHR));
    zox_log_vulkan(" > success creating vulkan surface\n")

    // link to our ecs
    *vk_instance = instance;
    *vk_surface = surface;
    const ecs_entity_t e = spawn_app_vulkan(world, window, vk_surface);
    zox_log_vulkan(" + success creating vulkan\n")

    // what dis do??
    create_vulkan_pipeline(world, vk_instance, vk_surface);

    return e;
}

// zox_component(VulkanInstance, VkInstance*)
// ECS_DTOR(VulkanSurface, ptr, { if (ptr->value != 0) vkDestroySurfaceKHR(*vk_instance, *ptr->value, NULL); })

/*uint find_present_queue_family_index(VkPhysicalDevice physicalDevice, VkSurfaceKHR surface) {
    uint queueFamilyCount = 0;
    vkGetPhysicalDeviceQueueFamilyProperties(physicalDevice, &queueFamilyCount, NULL);
    VkQueueFamilyProperties* queueFamilies = malloc(queueFamilyCount * sizeof(VkQueueFamilyProperties));
    if (!queueFamilies) {
        fprintf(stderr, "Failed to allocate memory for queue family properties!\n");
        return (uint)-1;
    }
    vkGetPhysicalDeviceQueueFamilyProperties(physicalDevice, &queueFamilyCount, queueFamilies);

    VkBool32 presentSupport = VK_FALSE;
    for (uint i = 0; i < queueFamilyCount; i++) {
        vkGetPhysicalDeviceSurfaceSupportKHR(physicalDevice, i, surface, &presentSupport);
        if (presentSupport) {
            free(queueFamilies);
            return i; // Return the index of the first queue family that supports presentation
        }
    }

    free(queueFamilies);
    return (uint)-1; // Return -1 if no suitable queue family was found
}*/

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
