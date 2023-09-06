#ifdef zoxel_include_vulkan
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
    }

    unsigned char create_main_window_vulkan(ecs_world_t *world) {
        zoxel_log(" > creating vulkan surface\n");
        // VkInstanceCreateInfo instanceCreateInfo = { };
        // instanceCreateInfo.sType = VK_STRUCTURE_TYPE_INSTANCE_CREATE_INFO;
        unsigned int extensionCount;
        if (!SDL_Vulkan_GetInstanceExtensions(window, &extensionCount, NULL)) {
            return EXIT_FAILURE;
        }
        const char** extensions = malloc(extensionCount * sizeof(const char*));
        if (!SDL_Vulkan_GetInstanceExtensions(window, &extensionCount, extensions)) {
            return EXIT_FAILURE;
        }
        zoxel_log(" > vulkan instance extensions [%i]:\n", extensionCount);
        for (unsigned int i = 0; i < extensionCount; i++) zoxel_log("     [%i]: %s\n", i, extensions[i]);
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
        spawn_app_vulkan(world, window, &surface);
        main_vulkan_context = &surface;
        main_vulkan_instance = &instance;
        return EXIT_SUCCESS;
    }
#endif