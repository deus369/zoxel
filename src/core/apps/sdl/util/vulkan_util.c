#ifdef zox_include_vulkan
// make VULKAN=1 && make run-vulkan

// todo:
//  1 Create Swap Chain
//  2 Create Graphics Pipeline
//  3 Finish this list

VkInstance* vk_instance = NULL;
VkSurfaceKHR* vk_surface = NULL;
// devices
VkDevice vk_device;
VkPhysicalDevice vk_physical_device;
// rendering
VkCommandPool vk_command_pool;
VkCommandBuffer vk_command_buffer;
VkExtent2D vk_swap_chain_extent;
VkRenderPass vk_render_pass;
VkFramebuffer vk_frame_buffer;
VkImageView vk_image_view;
VkSwapchainKHR vk_swap_chain;
VkQueue graphicsQueue;
VkQueue presentsQueue;
VkSemaphore vk_semaphore;
VkSemaphore vk_semaphore_image;
uint32_t queueFamilyIndex;
uint32_t vk_images_count;
float queuePriority = 1.0f;

zox_component(VulkanSurface, VkSurfaceKHR*)
// zox_component(VulkanInstance, VkInstance*)
ECS_DTOR(VulkanSurface, ptr, { if (ptr->value != 0) vkDestroySurfaceKHR(*vk_instance, *ptr->value, NULL); })

void dispose_vulkan_instance() {
    if (*vk_instance != VK_NULL_HANDLE) {
        zox_logg(" > destroying [vk_instance]\n")
        vkDestroyInstance(*vk_instance, NULL);
        *vk_instance = VK_NULL_HANDLE;
        // vkDestroyCommandPool(vk_device, vk_command_buffer, NULL);
        vkDestroyCommandPool(vk_device, vk_command_pool, NULL);
        vkDestroyRenderPass(vk_device, vk_render_pass, NULL);
        vkDestroyFramebuffer(vk_device, vk_frame_buffer, NULL);
        vkDestroyImageView(vk_device, vk_image_view, NULL);
        vkDestroySemaphore(vk_device, vk_semaphore, NULL);
        vkDestroySemaphore(vk_device, vk_semaphore_image, NULL);
        vkDestroyDevice(vk_device, NULL);
    }
}

void vulkan_clear_viewport(float3 clear_color) {
    // zox_logg(" > vulkan_clear_viewport\n")
    // VkSemaphore waitSemaphores[] = { vk_semaphore };
    uint32_t imageIndex;
    VkResult result = vkAcquireNextImageKHR(vk_device, vk_swap_chain, UINT64_MAX, vk_semaphore_image, VK_NULL_HANDLE, &imageIndex);
    // zox_log("imageIndex [%i]\n", imageIndex)
    // VkClearValue clearColor = { { clear_color.x, clear_color.y, clear_color.z, 1 } };
    VkClearValue clearColor = { clear_color.x, clear_color.y, clear_color.z, 1 };
    VkCommandBufferBeginInfo beginInfo = { };
    beginInfo.sType = VK_STRUCTURE_TYPE_COMMAND_BUFFER_BEGIN_INFO;
    // Render pass begin info
    VkRenderPassBeginInfo renderPassInfo = {};
    renderPassInfo.sType = VK_STRUCTURE_TYPE_RENDER_PASS_BEGIN_INFO;
    renderPassInfo.renderPass = vk_render_pass;
    renderPassInfo.framebuffer = vk_frame_buffer;
    renderPassInfo.renderArea.offset = (VkOffset2D) { 0, 0 };
    renderPassInfo.renderArea.extent = vk_swap_chain_extent;
    renderPassInfo.clearValueCount = 1;
    renderPassInfo.pClearValues = &clearColor;
    // data
    VkSemaphore waitSemaphores[] = { vk_semaphore_image };
    VkSemaphore signalSemaphores[] = { vk_semaphore };
    VkPipelineStageFlags waitStages[] = { VK_PIPELINE_STAGE_COLOR_ATTACHMENT_OUTPUT_BIT };
    // submit info
    VkSubmitInfo submitInfo = {};
    submitInfo.sType = VK_STRUCTURE_TYPE_SUBMIT_INFO;
    submitInfo.commandBufferCount = 1;
    submitInfo.pCommandBuffers = &vk_command_buffer;
    submitInfo.signalSemaphoreCount = 1;
    submitInfo.waitSemaphoreCount = 1;
    submitInfo.pWaitDstStageMask = waitStages;
    submitInfo.pWaitSemaphores = waitSemaphores;
    submitInfo.pSignalSemaphores = signalSemaphores;
    // present info
    VkPresentInfoKHR presentInfo = { };
    presentInfo.sType = VK_STRUCTURE_TYPE_PRESENT_INFO_KHR;
    VkSwapchainKHR swapChains[] = { vk_swap_chain };
    presentInfo.swapchainCount = 1;
    presentInfo.pSwapchains = swapChains;
    presentInfo.pImageIndices = &imageIndex;
    presentInfo.waitSemaphoreCount = 1;
    presentInfo.pWaitSemaphores = signalSemaphores;

    // Begin command buffer
    vkBeginCommandBuffer(vk_command_buffer, &beginInfo);
    // Begin and end the render pass
    vkCmdBeginRenderPass(vk_command_buffer, &renderPassInfo, VK_SUBPASS_CONTENTS_INLINE);
    vkCmdEndRenderPass(vk_command_buffer);
    // End command buffer
    vkEndCommandBuffer(vk_command_buffer);

    // Synchronization (Using fences or semaphores is recommended)
    VkFenceCreateInfo fenceInfo = {};
    fenceInfo.sType = VK_STRUCTURE_TYPE_FENCE_CREATE_INFO;
    VkFence fence;
    vkCreateFence(vk_device, &fenceInfo, NULL, &fence);

    // Submit the command buffer to the graphics queue
    vkQueueSubmit(graphicsQueue, 1, &submitInfo, fence); // VK_NULL_HANDLE fence);

    // Wait for the fence indefinitely
    vkWaitForFences(vk_device, 1, &fence, VK_TRUE, UINT64_MAX);
    // Destroy the fence after use
    vkDestroyFence(vk_device, fence, NULL);

    // In vkQueuePresentKHR
    vkQueuePresentKHR(presentsQueue, &presentInfo);
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

VkPhysicalDevice pick_physical_device(VkInstance instance) {
    VkPhysicalDevice physicalDevice = VK_NULL_HANDLE;
    uint32_t deviceCount = 0;
    vkEnumeratePhysicalDevices(instance, &deviceCount, NULL);
    if (deviceCount == 0) {
        fprintf(stderr, "Failed to find GPUs with Vulkan support!\n");
        return VK_NULL_HANDLE;
    }
    VkPhysicalDevice* devices = malloc(deviceCount * sizeof(VkPhysicalDevice));
    if (devices == NULL) {
        fprintf(stderr, "Failed to allocate memory for physical devices!\n");
        return VK_NULL_HANDLE;
    }
    vkEnumeratePhysicalDevices(instance, &deviceCount, devices);
    for (uint32_t i = 0; i < deviceCount; i++) {
        VkPhysicalDeviceProperties deviceProperties;
        vkGetPhysicalDeviceProperties(devices[i], &deviceProperties);
        if (deviceProperties.deviceType == VK_PHYSICAL_DEVICE_TYPE_DISCRETE_GPU) {
            physicalDevice = devices[i];
            break;
        }
    }
    if (physicalDevice == VK_NULL_HANDLE && deviceCount > 0) {
        // Fallback to the first device if no discrete GPU is found
        physicalDevice = devices[0];
    }
    free(devices);
    return physicalDevice;
}

uint32_t find_graphics_queue_family_index(VkPhysicalDevice physicalDevice) {
    uint32_t queueFamilyCount = 0;
    vkGetPhysicalDeviceQueueFamilyProperties(physicalDevice, &queueFamilyCount, NULL);
    VkQueueFamilyProperties* queueFamilies = malloc(queueFamilyCount * sizeof(VkQueueFamilyProperties));
    if (!queueFamilies) {
        fprintf(stderr, "Failed to allocate memory for queue family properties!\n");
        return (uint32_t)-1;
    }
    vkGetPhysicalDeviceQueueFamilyProperties(physicalDevice, &queueFamilyCount, queueFamilies);
    for (uint32_t i = 0; i < queueFamilyCount; i++) {
        if (queueFamilies[i].queueFlags & VK_QUEUE_GRAPHICS_BIT) {
            free(queueFamilies);
            return i; // Return the index of the first queue family that supports graphics
        }
    }
    free(queueFamilies);
    return (uint32_t)-1; // Return -1 if no suitable queue family was found
}

unsigned char vulkan_create_device() {
    vk_physical_device = pick_physical_device(*vk_instance);
    if (vk_physical_device == VK_NULL_HANDLE) {
        fprintf(stderr, "Failed to find a suitable GPU!\n");
        return EXIT_FAILURE;
    }
    // Find the queue family index for the graphics queue
    queueFamilyIndex = find_graphics_queue_family_index(vk_physical_device);
    if (queueFamilyIndex == (uint32_t)-1) {
        fprintf(stderr, "Failed to find a suitable queue family!\n");
        return EXIT_FAILURE;
    }
    VkPhysicalDeviceFeatures deviceFeatures = { };
    const char* deviceExtensions[] = { "VK_KHR_swapchain" };
    uint32_t deviceExtensionCount = 1;
    // queue
    VkDeviceQueueCreateInfo queueCreateInfo = { };
    queueCreateInfo.sType = VK_STRUCTURE_TYPE_DEVICE_QUEUE_CREATE_INFO;
    queueCreateInfo.queueFamilyIndex = queueFamilyIndex;
    queueCreateInfo.queueCount = 1;
    queueCreateInfo.pQueuePriorities = &queuePriority;
    VkDeviceCreateInfo deviceCreateInfo = { };
    deviceCreateInfo.sType = VK_STRUCTURE_TYPE_DEVICE_CREATE_INFO;
    deviceCreateInfo.pQueueCreateInfos = &queueCreateInfo;
    deviceCreateInfo.queueCreateInfoCount = 1;
    deviceCreateInfo.pEnabledFeatures = &deviceFeatures;
    deviceCreateInfo.ppEnabledExtensionNames = deviceExtensions;
    deviceCreateInfo.enabledExtensionCount = deviceExtensionCount;
    // Create the logical device vk_device
    VkResult deviceResult = vkCreateDevice(vk_physical_device, &deviceCreateInfo, NULL, &vk_device);
    if (deviceResult != VK_SUCCESS) {
        zox_log(" ! failed to create logical device [%s]\n", vulkan_result_to_string(deviceResult))
        return EXIT_FAILURE;
    }
    return EXIT_SUCCESS;
}

unsigned char vulkan_create_command_buffer() {
    // Create a Command Pool
    VkCommandPoolCreateInfo poolCreateInfo = {};
    poolCreateInfo.sType = VK_STRUCTURE_TYPE_COMMAND_POOL_CREATE_INFO;
    poolCreateInfo.flags = VK_COMMAND_POOL_CREATE_RESET_COMMAND_BUFFER_BIT;
    poolCreateInfo.queueFamilyIndex = queueFamilyIndex;
    VkResult poolResult = vkCreateCommandPool(vk_device, &poolCreateInfo, NULL, &vk_command_pool);
    if (poolResult != VK_SUCCESS) {
        zoxel_log(" ! failed to create command pool [%s]\n", vulkan_result_to_string(poolResult));
        // Cleanup and exit logic
        return EXIT_FAILURE;
    }
    // Allocate a Command Buffer
    VkCommandBufferAllocateInfo allocInfo = {};
    allocInfo.sType = VK_STRUCTURE_TYPE_COMMAND_BUFFER_ALLOCATE_INFO;
    allocInfo.commandPool = vk_command_pool;
    allocInfo.level = VK_COMMAND_BUFFER_LEVEL_PRIMARY;
    allocInfo.commandBufferCount = 1;
    // creates vk_command_buffer
    VkResult bufferResult = vkAllocateCommandBuffers(vk_device, &allocInfo, &vk_command_buffer);
    if (bufferResult != VK_SUCCESS) {
        zoxel_log(" ! failed to allocate command buffer [%s]\n", vulkan_result_to_string(bufferResult));
        // Cleanup and exit logic
        return EXIT_FAILURE;
    }
    return EXIT_SUCCESS;
}

unsigned create_vulkan_render_pass() {
    VkAttachmentDescription colorAttachment = { };
    colorAttachment.format = VK_FORMAT_B8G8R8A8_UNORM;
    colorAttachment.samples = VK_SAMPLE_COUNT_1_BIT;
    colorAttachment.loadOp = VK_ATTACHMENT_LOAD_OP_CLEAR;
    colorAttachment.storeOp = VK_ATTACHMENT_STORE_OP_STORE;
    colorAttachment.stencilLoadOp = VK_ATTACHMENT_LOAD_OP_DONT_CARE;
    colorAttachment.stencilStoreOp = VK_ATTACHMENT_STORE_OP_DONT_CARE;
    colorAttachment.initialLayout = VK_IMAGE_LAYOUT_UNDEFINED;
    colorAttachment.finalLayout = VK_IMAGE_LAYOUT_PRESENT_SRC_KHR;
    // Subpass description
    VkSubpassDescription subpass = { };
    subpass.pipelineBindPoint = VK_PIPELINE_BIND_POINT_GRAPHICS;
    subpass.colorAttachmentCount = 1;
    VkAttachmentReference colorAttachmentRef = { 0, VK_IMAGE_LAYOUT_COLOR_ATTACHMENT_OPTIMAL };
    subpass.pColorAttachments = &colorAttachmentRef;
    // render pass dependency
    VkSubpassDependency dependency = {};
    dependency.srcSubpass = VK_SUBPASS_EXTERNAL;
    dependency.dstSubpass = 0;
    dependency.srcStageMask = VK_PIPELINE_STAGE_COLOR_ATTACHMENT_OUTPUT_BIT;
    dependency.srcAccessMask = 0;
    dependency.dstStageMask = VK_PIPELINE_STAGE_COLOR_ATTACHMENT_OUTPUT_BIT;
    dependency.dstAccessMask = VK_ACCESS_COLOR_ATTACHMENT_READ_BIT | VK_ACCESS_COLOR_ATTACHMENT_WRITE_BIT;
    // Render pass creation
    VkRenderPassCreateInfo renderPassInfo = { };
    renderPassInfo.sType = VK_STRUCTURE_TYPE_RENDER_PASS_CREATE_INFO;
    renderPassInfo.attachmentCount = 1;
    renderPassInfo.pAttachments = &colorAttachment;
    renderPassInfo.subpassCount = 1;
    renderPassInfo.pSubpasses = &subpass;
    renderPassInfo.dependencyCount = 1; // Add this line
    renderPassInfo.pDependencies = &dependency; // Add this line
    // creates our vk_render_pass
    VkResult renderPassResult = vkCreateRenderPass(vk_device, &renderPassInfo, NULL, &vk_render_pass);
    if (renderPassResult != VK_SUCCESS) {
        zoxel_log(" ! failed to create render pass [%s]\n", vulkan_result_to_string(renderPassResult));
        // Cleanup and exit logic
        return EXIT_FAILURE;
    }

    return EXIT_SUCCESS;
}

VkSurfaceFormatKHR choose_surface_format(VkPhysicalDevice physicalDevice, VkSurfaceKHR surface) {
    uint32_t formatCount;
    vkGetPhysicalDeviceSurfaceFormatsKHR(physicalDevice, surface, &formatCount, NULL);
    if (formatCount == 0) {
        fprintf(stderr, "Failed to find any surface formats.\n");
        return (VkSurfaceFormatKHR){ 0 }; // Return an empty VkSurfaceFormatKHR struct
    }
    VkSurfaceFormatKHR* formats = malloc(formatCount * sizeof(VkSurfaceFormatKHR));
    if (!formats) {
        fprintf(stderr, "Failed to allocate memory for surface formats.\n");
        return (VkSurfaceFormatKHR){ 0 };
    }
    vkGetPhysicalDeviceSurfaceFormatsKHR(physicalDevice, surface, &formatCount, formats);
    // zox_log(" + formats found [%i]\n", formatCount)
    VkSurfaceFormatKHR chosenFormat;
    if (formatCount == 0 || (formatCount == 1 && formats[0].format == VK_FORMAT_UNDEFINED)) {
        zox_logg(" ! format is undefined\n")
        chosenFormat = (VkSurfaceFormatKHR){ VK_FORMAT_B8G8R8A8_UNORM, VK_COLOR_SPACE_SRGB_NONLINEAR_KHR };
    } else {
        // Search for a preferred format, or pick the first one as a fallback
        chosenFormat = formats[0];
        for (uint32_t i = 0; i < formatCount; i++) {
            if (formats[i].format == VK_FORMAT_B8G8R8A8_UNORM && formats[i].colorSpace == VK_COLOR_SPACE_SRGB_NONLINEAR_KHR) {
                chosenFormat = formats[i];
                // zox_log(" + format chose [%i]\n", i)
                break;
            }
        }
    }
    free(formats);
    return chosenFormat;
}

VkPresentModeKHR choose_swap_present_mode(VkPhysicalDevice physicalDevice, VkSurfaceKHR surface) {
    uint32_t presentModeCount;
    vkGetPhysicalDeviceSurfacePresentModesKHR(physicalDevice, surface, &presentModeCount, NULL);
    if (presentModeCount == 0) {
        fprintf(stderr, "Failed to find any present modes.\n");
        return VK_PRESENT_MODE_FIFO_KHR; // FIFO is guaranteed to be available
    }
    VkPresentModeKHR* presentModes = malloc(presentModeCount * sizeof(VkPresentModeKHR));
    if (!presentModes) {
        fprintf(stderr, "Failed to allocate memory for present modes.\n");
        return VK_PRESENT_MODE_FIFO_KHR;
    }
    vkGetPhysicalDeviceSurfacePresentModesKHR(physicalDevice, surface, &presentModeCount, presentModes);
    // zox_log(" + present modes found [%i]\n", presentModeCount)
    VkPresentModeKHR chosenPresentMode = VK_PRESENT_MODE_FIFO_KHR; // Default to FIFO mode
    for (uint32_t i = 0; i < presentModeCount; i++) {
        if (presentModes[i] == VK_PRESENT_MODE_MAILBOX_KHR) {
            chosenPresentMode = VK_PRESENT_MODE_MAILBOX_KHR;
            zox_log(" + present mode chose [%i]\n", i)
            break;
        }
    }
    free(presentModes);
    return chosenPresentMode;
}

void log_swap_chain_create_info(const VkSwapchainCreateInfoKHR *createInfo) {
    zox_logg("Swap Chain Create Info:\n");
    zox_log("  sType: %d\n", createInfo->sType);
    zox_log("  surface: %p\n", (void*)createInfo->surface);
    zox_log("  minImageCount: %u\n", createInfo->minImageCount);
    zox_log("  imageFormat: %d\n", createInfo->imageFormat);
    zox_log("  imageColorSpace: %d\n", createInfo->imageColorSpace);
    zox_log("  imageExtent.width: %u\n", createInfo->imageExtent.width);
    zox_log("  imageExtent.height: %u\n", createInfo->imageExtent.height);
    zox_log("  imageArrayLayers: %u\n", createInfo->imageArrayLayers);
    zox_log("  imageUsage: %u\n", createInfo->imageUsage);
    zox_log("  imageSharingMode: %d\n", createInfo->imageSharingMode);
    zox_log("  compositeAlpha: %u\n", createInfo->compositeAlpha);
    zox_log("  clipped: %u\n", createInfo->clipped);
    zox_log("  oldSwapchain: %p\n", (void*)createInfo->oldSwapchain);
    zox_log("  preTransform: %u\n", createInfo->preTransform);
    zox_log("  presentMode: %u\n", createInfo->presentMode);
}

unsigned char create_vulkan_swap_chain() {
    VkBool32 presentSupport = VK_FALSE;
    vkGetPhysicalDeviceSurfaceSupportKHR(vk_physical_device, queueFamilyIndex, *vk_surface, &presentSupport);
    if (!presentSupport) return EXIT_FAILURE;
    // Query surface capabilities for preTransform and present mode
    VkSurfaceCapabilitiesKHR surfaceCapabilities;
    vkGetPhysicalDeviceSurfaceCapabilitiesKHR(vk_physical_device, *vk_surface, &surfaceCapabilities);
    vk_swap_chain_extent = surfaceCapabilities.currentExtent;
    vk_images_count = surfaceCapabilities.minImageCount  + 1;
    VkPresentModeKHR presentMode = choose_swap_present_mode(vk_physical_device, *vk_surface);
    // VK_PRESENT_MODE_FIFO_KHR;
    VkSurfaceFormatKHR surfaceFormat = choose_surface_format(vk_physical_device, *vk_surface);
    VkSwapchainCreateInfoKHR createInfo = { };
    createInfo.sType = VK_STRUCTURE_TYPE_SWAPCHAIN_CREATE_INFO_KHR;
    createInfo.surface = *vk_surface;
    createInfo.imageFormat = surfaceFormat.format;
    createInfo.imageColorSpace = surfaceFormat.colorSpace;
    createInfo.minImageCount = vk_images_count;
    createInfo.imageExtent = vk_swap_chain_extent;
    createInfo.imageArrayLayers = 1;
    createInfo.imageUsage = VK_IMAGE_USAGE_COLOR_ATTACHMENT_BIT;
    createInfo.imageSharingMode = VK_SHARING_MODE_EXCLUSIVE; // Depends on queue family setup
    createInfo.compositeAlpha = VK_COMPOSITE_ALPHA_OPAQUE_BIT_KHR;
    createInfo.clipped = VK_TRUE;
    createInfo.oldSwapchain = VK_NULL_HANDLE;
    createInfo.preTransform = surfaceCapabilities.currentTransform;
    createInfo.presentMode = presentMode;
    // log_swap_chain_create_info(&createInfo);
    // return EXIT_SUCCESS;
    VkResult swapChainResults = vkCreateSwapchainKHR(vk_device, &createInfo, NULL, &vk_swap_chain);
    if (swapChainResults != VK_SUCCESS) {
        // Handle swap chain creation failure
        zox_log(" ! failed vkCreateSwapchainKHR [%s]\n", vulkan_result_to_string(swapChainResults))
        return EXIT_FAILURE;
    }
    // zox_logg(" ! vkCreateSwapchainKHR success.\n")
    return EXIT_SUCCESS;
}


unsigned char create_vulkan_frame_buffer() {
    // swap chain images
    VkResult swapChainImagesCountResult = vkGetSwapchainImagesKHR(vk_device, vk_swap_chain, &vk_images_count, NULL);
    if (swapChainImagesCountResult != VK_SUCCESS) {
        zox_logg(" ! failed to get swap chain images\n")
        return EXIT_FAILURE;
    }
    zox_log(" images count [%i]\n", vk_images_count)
    VkImage* vk_swap_chain_images = malloc(vk_images_count * sizeof(VkImage));
    if (vk_swap_chain_images == NULL) {
        zox_logg(" ! vk_swap_chain_images is null\n")
        return EXIT_FAILURE;
    }
    VkResult swapChainImagesResult = vkGetSwapchainImagesKHR(vk_device, vk_swap_chain, &vk_images_count, vk_swap_chain_images);
    if (swapChainImagesResult != VK_SUCCESS) {
        zoxel_log(" ! failed to get swap chain images [%s]\n", vulkan_result_to_string(swapChainImagesResult));
        free(vk_swap_chain_images);
        return EXIT_FAILURE;
    }
    // image view
    VkImageViewCreateInfo viewCreateInfo = {};
    viewCreateInfo.sType = VK_STRUCTURE_TYPE_IMAGE_VIEW_CREATE_INFO;
    viewCreateInfo.image = vk_swap_chain_images[0]; // Assuming you are creating the view for the first image
    viewCreateInfo.viewType = VK_IMAGE_VIEW_TYPE_2D;
    viewCreateInfo.format = VK_FORMAT_B8G8R8A8_UNORM; // This should match the swap chain image format
    viewCreateInfo.components.r = VK_COMPONENT_SWIZZLE_IDENTITY;
    viewCreateInfo.components.g = VK_COMPONENT_SWIZZLE_IDENTITY;
    viewCreateInfo.components.b = VK_COMPONENT_SWIZZLE_IDENTITY;
    viewCreateInfo.components.a = VK_COMPONENT_SWIZZLE_IDENTITY;
    viewCreateInfo.subresourceRange.aspectMask = VK_IMAGE_ASPECT_COLOR_BIT;
    viewCreateInfo.subresourceRange.baseMipLevel = 0;
    viewCreateInfo.subresourceRange.levelCount = 1;
    viewCreateInfo.subresourceRange.baseArrayLayer = 0;
    viewCreateInfo.subresourceRange.layerCount = 1;

    // creates vk_image_view
    VkResult imageViewResult = vkCreateImageView(vk_device, &viewCreateInfo, NULL, &vk_image_view);

    free(vk_swap_chain_images);

    if (imageViewResult != VK_SUCCESS) {
        zoxel_log(" ! failed to create image view [%s]\n", vulkan_result_to_string(imageViewResult));
        // Cleanup and exit logic
        return EXIT_FAILURE;
    }

    // For simplicity, assuming a single imageView (in a real scenario, you'd loop over all swap chain images)
    VkImageView attachments[] = { vk_image_view };

    // Create Framebuffer
    VkFramebufferCreateInfo framebufferInfo = {};
    framebufferInfo.sType = VK_STRUCTURE_TYPE_FRAMEBUFFER_CREATE_INFO;
    framebufferInfo.renderPass = vk_render_pass;
    framebufferInfo.attachmentCount = 1;
    framebufferInfo.pAttachments = attachments;
    framebufferInfo.width = vk_swap_chain_extent.width;
    framebufferInfo.height = vk_swap_chain_extent.height;
    framebufferInfo.layers = 1;

    // creates vk_frame_buffer
    VkResult framebufferResult = vkCreateFramebuffer(vk_device, &framebufferInfo, NULL, &vk_frame_buffer);
    if (framebufferResult != VK_SUCCESS) {
        zoxel_log(" ! failed to create framebuffer [%s]\n", vulkan_result_to_string(framebufferResult));
        // Cleanup and exit logic
        return EXIT_FAILURE;
    }

    return EXIT_SUCCESS;
}
// Define a callback function
VKAPI_ATTR VkBool32 VKAPI_CALL debugCallback(VkDebugUtilsMessageSeverityFlagBitsEXT messageSeverity, VkDebugUtilsMessageTypeFlagsEXT messageType, const VkDebugUtilsMessengerCallbackDataEXT* pCallbackData, void* pUserData) {
    fprintf(stderr, "Validation layer: %s\n", pCallbackData->pMessage);
    return VK_FALSE;
}

// Function to create the debug messenger
VkResult CreateDebugUtilsMessengerEXT(VkInstance instance, const VkDebugUtilsMessengerCreateInfoEXT* pCreateInfo, const VkAllocationCallbacks* pAllocator, VkDebugUtilsMessengerEXT* pDebugMessenger) {
    PFN_vkCreateDebugUtilsMessengerEXT func = (PFN_vkCreateDebugUtilsMessengerEXT) vkGetInstanceProcAddr(instance, "vkCreateDebugUtilsMessengerEXT");
    if (func != NULL) {
        return func(instance, pCreateInfo, pAllocator, pDebugMessenger);
    } else {
        return VK_ERROR_EXTENSION_NOT_PRESENT;
    }
}

unsigned char create_vulkan_debugger() {
    // When setting up your Vulkan instance and devices
    VkDebugUtilsMessengerCreateInfoEXT createInfo = {};
    createInfo.sType = VK_STRUCTURE_TYPE_DEBUG_UTILS_MESSENGER_CREATE_INFO_EXT;
    createInfo.messageSeverity = VK_DEBUG_UTILS_MESSAGE_SEVERITY_VERBOSE_BIT_EXT | VK_DEBUG_UTILS_MESSAGE_SEVERITY_WARNING_BIT_EXT | VK_DEBUG_UTILS_MESSAGE_SEVERITY_ERROR_BIT_EXT;
    createInfo.messageType = VK_DEBUG_UTILS_MESSAGE_TYPE_GENERAL_BIT_EXT | VK_DEBUG_UTILS_MESSAGE_TYPE_VALIDATION_BIT_EXT | VK_DEBUG_UTILS_MESSAGE_TYPE_PERFORMANCE_BIT_EXT;
    createInfo.pfnUserCallback = debugCallback;
    VkDebugUtilsMessengerEXT debugMessenger;
    if (CreateDebugUtilsMessengerEXT(*vk_instance, &createInfo, NULL, &debugMessenger) != VK_SUCCESS) {
        // Handle error
        return EXIT_FAILURE;
    }
    return EXIT_SUCCESS;
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
        zox_log(" ! failed to create vulkan instance [%s]\n", vulkan_result_to_string(result))
        return EXIT_FAILURE;
    }
    VkSurfaceKHR surface = create_vulkan_surface(window, instance);
    if (surface == NULL) {
        zox_logg(" ! failed to create VkSurfaceKHR\n")
        return EXIT_FAILURE;
    }
    vk_instance = malloc(sizeof(VkInstance));
    vk_surface = malloc(sizeof(VkSurfaceKHR));
    *vk_instance = instance;
    *vk_surface = surface;
    zox_logg(" > success creating vulkan surface\n")

    //if (create_vulkan_debugger() == EXIT_FAILURE) return EXIT_FAILURE;
    //zox_logg(" > success creating vulkan debugger\n")

    if (vulkan_create_device() == EXIT_FAILURE) return EXIT_FAILURE;
    zox_logg(" > success creating vulkan device\n")

    // get queues
    uint32_t queueFamilyCount = 0;
    vkGetPhysicalDeviceQueueFamilyProperties(vk_physical_device, &queueFamilyCount, NULL);
    VkQueueFamilyProperties queueFamilies[queueFamilyCount];
    vkGetPhysicalDeviceQueueFamilyProperties(vk_physical_device, &queueFamilyCount, queueFamilies);
    VkBool32 presentSupport = VK_FALSE;
    int presentQueueFamilyIndex = -1;
    for (uint32_t i = 0; i < queueFamilyCount; i++) {
        vkGetPhysicalDeviceSurfaceSupportKHR(vk_physical_device, i, *vk_surface, &presentSupport);
        if (queueFamilies[i].queueFlags & VK_QUEUE_GRAPHICS_BIT && presentSupport) {
            presentQueueFamilyIndex = i;
            break;
        }
    }
    vkGetDeviceQueue(vk_device, presentQueueFamilyIndex, 0, &presentsQueue);
    vkGetDeviceQueue(vk_device, queueFamilyIndex, 0, &graphicsQueue);

    if (vulkan_create_command_buffer() == EXIT_FAILURE) return EXIT_FAILURE;
    zox_logg(" > success creating vulkan command_buffer\n")

    // Swap Chain Extent
    int width, height;
    SDL_Vulkan_GetDrawableSize(window, &width, &height);
    vk_swap_chain_extent = (VkExtent2D) { width, height };

    if (create_vulkan_render_pass() == EXIT_FAILURE) return EXIT_FAILURE;
    zox_logg(" > success creating vulkan render_pass\n")

    if (create_vulkan_swap_chain() == EXIT_FAILURE) return EXIT_FAILURE;
    zox_logg(" > success creating vulkan swap_chain\n")

    if (create_vulkan_frame_buffer() == EXIT_FAILURE) return EXIT_FAILURE;
    zox_logg(" > success creating vulkan frame_buffer\n")

    VkSemaphoreCreateInfo semaphoreInfo = {};
    semaphoreInfo.sType = VK_STRUCTURE_TYPE_SEMAPHORE_CREATE_INFO;
    VkResult sepaphoreResult = vkCreateSemaphore(vk_device, &semaphoreInfo, NULL, &vk_semaphore);
    if (sepaphoreResult != VK_SUCCESS) {
        zox_log(" ! failed to vk_semaphore [%s]\n", vulkan_result_to_string(sepaphoreResult))
        return EXIT_FAILURE;
    }

    VkResult semaphoreImageResult = vkCreateSemaphore(vk_device, &semaphoreInfo, NULL, &vk_semaphore_image);
    if (semaphoreImageResult != VK_SUCCESS) {
        zox_log(" ! failed to create vk_semaphore_image [%s]\n", vulkan_result_to_string(semaphoreImageResult));
        return EXIT_FAILURE;
    }

    // link to our ecs
    spawn_app_vulkan(world, window, vk_surface);
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
