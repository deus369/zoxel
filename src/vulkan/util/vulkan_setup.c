// vulkan variables global
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
VkFramebuffer* vk_frame_buffers;
VkImageView *vk_image_views;
VkSwapchainKHR vk_swap_chain;
uint queue_family_index;
VkQueue graphics_queue;
// VkQueue presents_queue;
VkSemaphore vk_semaphore;
VkSemaphore vk_semaphore_image;
uint vk_images_count;
float queuePriority = 1.0f;
VkFence vk_fence;
uint vk_image_index;

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

void dispose_vulkan_globals() {
    if (*vk_instance != VK_NULL_HANDLE) {
        zox_log_vulkan(" > destroying [vk_instance]\n")
        // vkDestroyCommandPool(vk_device, vk_command_buffer, NULL);
        vkDestroyCommandPool(vk_device, vk_command_pool, NULL);
        vkDestroyRenderPass(vk_device, vk_render_pass, NULL);
        for (int i = 0; i < vk_images_count; i++) vkDestroyFramebuffer(vk_device, vk_frame_buffers[i], NULL);
        for (int i = 0; i < vk_images_count; i++) vkDestroyImageView(vk_device, vk_image_views[i], NULL);
        free(vk_frame_buffers);
        free(vk_image_views);
        vkDestroySemaphore(vk_device, vk_semaphore, NULL);
        vkDestroySemaphore(vk_device, vk_semaphore_image, NULL);
        vkDestroyFence(vk_device, vk_fence, NULL);
        vkDestroyDevice(vk_device, NULL);
        vkDestroySurfaceKHR(*vk_instance, *vk_surface, NULL);
        vkDestroyInstance(*vk_instance, NULL);
    }
}

void vulkan_get_image_index() {
    // imageIndex (on swap chain)
    VkResult result = vkAcquireNextImageKHR(vk_device, vk_swap_chain, UINT64_MAX, vk_semaphore_image, VK_NULL_HANDLE, &vk_image_index);
    if (result != VK_SUCCESS && result != VK_SUBOPTIMAL_KHR) {
        zox_log_vulkan(" ! failed to create logical device [%s]\n", vulkan_result_to_string(result))
        return;
    }
}

// Synchronization (Using fences or semaphores is recommended)
void vulkan_synchronize() {
    VkSemaphore signalSemaphores[] = { vk_semaphore };
    VkSemaphore waitSemaphores[] = { vk_semaphore_image };
    VkPipelineStageFlags waitStages[] = { VK_PIPELINE_STAGE_COLOR_ATTACHMENT_OUTPUT_BIT };
    VkSwapchainKHR swapChains[] = { vk_swap_chain };

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

    // submit graphics queue
    vkQueueSubmit(graphics_queue, 1, &submitInfo, vk_fence);
    vkWaitForFences(vk_device, 1, &vk_fence, VK_TRUE, UINT64_MAX);
    vkResetFences(vk_device, 1, &vk_fence);

    // present info
    VkPresentInfoKHR presentInfo = { };
    presentInfo.sType = VK_STRUCTURE_TYPE_PRESENT_INFO_KHR;
    presentInfo.swapchainCount = 1;
    presentInfo.pSwapchains = swapChains;
    presentInfo.pImageIndices = &vk_image_index;
    presentInfo.waitSemaphoreCount = 1;
    presentInfo.pWaitSemaphores = signalSemaphores;

    // submit queues and wait for gpu
    vkQueuePresentKHR(graphics_queue, &presentInfo); // presents_queue
}

void vulkan_begin_render_pass(VkClearValue clear_color) {
    vulkan_get_image_index();
    // VkClearValue clearValues[1];
    // Clear to a sky blue color for the color attachment
    // clearValues[0].color = (VkClearValue) { 1.0f, 0.0f, 0.0f, 1.0f };
    // Clear the depth buffer to 1.0 (farthest) and stencil to 0
    // clearValues[1].depthStencil = (VkClearDepthStencilValue) {1.0f, 0};
    // VkClearValue clearColor2 = (VkClearValue) {{{ 1.0f, 0.0f, 0.0f, 1.0f }}};
    // Begin Command Buffer
    VkCommandBufferBeginInfo beginInfo = { };
    beginInfo.sType = VK_STRUCTURE_TYPE_COMMAND_BUFFER_BEGIN_INFO;
    vkBeginCommandBuffer(vk_command_buffer, &beginInfo);
    // Begin Render Pass
    VkRenderPassBeginInfo renderPassInfo = { };
    renderPassInfo.sType = VK_STRUCTURE_TYPE_RENDER_PASS_BEGIN_INFO;
    renderPassInfo.renderPass = vk_render_pass;
    renderPassInfo.framebuffer = vk_frame_buffers[vk_image_index];
    renderPassInfo.renderArea.offset = (VkOffset2D) { 0, 0 };
    renderPassInfo.renderArea.extent = vk_swap_chain_extent;
    renderPassInfo.clearValueCount = 1;         // 1
    renderPassInfo.pClearValues = &clear_color;  // &clearColor;
    vkCmdBeginRenderPass(vk_command_buffer, &renderPassInfo, VK_SUBPASS_CONTENTS_INLINE);
}

void vulkan_end_render_pass() {
    vkCmdEndRenderPass(vk_command_buffer);
    vkEndCommandBuffer(vk_command_buffer);
    vulkan_synchronize();
}

void vulkan_clear_viewport(float3 clear_color) {
    VkClearValue vk_clear_color = { clear_color.x, clear_color.y, clear_color.z, 1 };
    vulkan_begin_render_pass(vk_clear_color);
    vulkan_end_render_pass();
}

VkSurfaceKHR create_vulkan_surface( SDL_Window* window, VkInstance instance) {
    VkSurfaceKHR surface;
    if (!SDL_Vulkan_CreateSurface(window, instance, &surface)) {
        zox_log_vulkan(" ! failed to create vulkan surface [%s]\n", SDL_GetError())
        return VK_NULL_HANDLE;
    }
    return surface;
}

VkPhysicalDevice pick_physical_device(VkInstance instance) {
    VkPhysicalDevice physicalDevice = VK_NULL_HANDLE;
    uint deviceCount = 0;
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
    for (uint i = 0; i < deviceCount; i++) {
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



uint find_graphics_queue_family_index(VkPhysicalDevice physicalDevice) {
    uint queueFamilyCount = 0;
    vkGetPhysicalDeviceQueueFamilyProperties(physicalDevice, &queueFamilyCount, NULL);
    VkQueueFamilyProperties* queueFamilies = malloc(queueFamilyCount * sizeof(VkQueueFamilyProperties));
    if (!queueFamilies) {
        fprintf(stderr, "Failed to allocate memory for queue family properties!\n");
        return (uint) -1;
    }
    vkGetPhysicalDeviceQueueFamilyProperties(physicalDevice, &queueFamilyCount, queueFamilies);
    for (uint i = 0; i < queueFamilyCount; i++) {
        if (queueFamilies[i].queueFlags & VK_QUEUE_GRAPHICS_BIT) {
            free(queueFamilies);
            return i; // Return the index of the first queue family that supports graphics
        }
    }
    free(queueFamilies);
    return (uint) -1; // Return -1 if no suitable queue family was found
}

uint find_graphics_and_present_queue_family_index(VkPhysicalDevice physicalDevice, VkSurfaceKHR surface) {
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
        if ((queueFamilies[i].queueFlags & VK_QUEUE_GRAPHICS_BIT) && presentSupport) {
            free(queueFamilies);
            return i; // Return the index of the first queue family that supports both graphics and presentation
        }
    }

    free(queueFamilies);
    return (uint)-1; // Return -1 if no suitable queue family was found
}

byte vulkan_create_device() {
    const char* deviceExtensions[] = { "VK_KHR_swapchain" };
    uint deviceExtensionCount = 1;

    vk_physical_device = pick_physical_device(*vk_instance);
    if (vk_physical_device == VK_NULL_HANDLE) {
        fprintf(stderr, "Failed to find a suitable GPU!\n");
        return EXIT_FAILURE;
    }

    // Find the queue family index for the graphics queue
    queue_family_index = find_graphics_and_present_queue_family_index(vk_physical_device, *vk_surface);
    // find_graphics_queue_family_index(vk_physical_device);
    if (queue_family_index == (uint) -1) {
        fprintf(stderr, "Failed to find a suitable queue family!\n");
        return EXIT_FAILURE;
    }

    // queue
    VkDeviceQueueCreateInfo queueCreateInfo = { };
    queueCreateInfo.sType = VK_STRUCTURE_TYPE_DEVICE_QUEUE_CREATE_INFO;
    queueCreateInfo.queueFamilyIndex = queue_family_index;
    queueCreateInfo.queueCount = 1;
    queueCreateInfo.pQueuePriorities = &queuePriority;

    // device creation
    VkDeviceCreateInfo deviceCreateInfo = { };
    deviceCreateInfo.sType = VK_STRUCTURE_TYPE_DEVICE_CREATE_INFO;
    deviceCreateInfo.pQueueCreateInfos = &queueCreateInfo;
    deviceCreateInfo.queueCreateInfoCount = 1;
    VkPhysicalDeviceFeatures deviceFeatures = { };
    deviceCreateInfo.pEnabledFeatures = &deviceFeatures;
    deviceCreateInfo.ppEnabledExtensionNames = deviceExtensions;
    deviceCreateInfo.enabledExtensionCount = deviceExtensionCount;

    // Create the logical device vk_device
    VkResult deviceResult = vkCreateDevice(vk_physical_device, &deviceCreateInfo, NULL, &vk_device);
    if (deviceResult != VK_SUCCESS) {
        zox_log_vulkan(" ! failed to create logical device [%s]\n", vulkan_result_to_string(deviceResult))
        return EXIT_FAILURE;
    }
    return EXIT_SUCCESS;
}

byte vulkan_create_command_buffer() {
    // Create a Command Pool
    VkCommandPoolCreateInfo poolCreateInfo = {};
    poolCreateInfo.sType = VK_STRUCTURE_TYPE_COMMAND_POOL_CREATE_INFO;
    poolCreateInfo.flags = VK_COMMAND_POOL_CREATE_RESET_COMMAND_BUFFER_BIT;
    poolCreateInfo.queueFamilyIndex = queue_family_index;
    VkResult poolResult = vkCreateCommandPool(vk_device, &poolCreateInfo, NULL, &vk_command_pool);
    if (poolResult != VK_SUCCESS) {
        zox_log_vulkan(" ! failed to create command pool [%s]\n", vulkan_result_to_string(poolResult))
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
        zox_log_vulkan(" ! failed to allocate command buffer [%s]\n", vulkan_result_to_string(bufferResult))
        // Cleanup and exit logic
        return EXIT_FAILURE;
    }
    return EXIT_SUCCESS;
}

unsigned create_vulkan_render_pass() {
    VkAttachmentDescription colorAttachment = { };
    colorAttachment.format = VK_FORMAT_B8G8R8A8_UNORM;
    colorAttachment.samples = VK_SAMPLE_COUNT_1_BIT;
    colorAttachment.loadOp = VK_ATTACHMENT_LOAD_OP_CLEAR; // automatic clearing for color
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
        zox_log_vulkan(" ! failed to create render pass [%s]\n", vulkan_result_to_string(renderPassResult))
        // Cleanup and exit logic
        return EXIT_FAILURE;
    }

    return EXIT_SUCCESS;
}

VkSurfaceFormatKHR choose_surface_format(VkPhysicalDevice physicalDevice, VkSurfaceKHR surface) {
    uint formatCount;
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
    VkSurfaceFormatKHR chosenFormat;
    if (formatCount == 0 || (formatCount == 1 && formats[0].format == VK_FORMAT_UNDEFINED)) {
        zox_log_vulkan(" ! format is undefined\n")
        chosenFormat = (VkSurfaceFormatKHR){ VK_FORMAT_B8G8R8A8_UNORM, VK_COLOR_SPACE_SRGB_NONLINEAR_KHR };
    } else {
        // Search for a preferred format, or pick the first one as a fallback
        chosenFormat = formats[0];
        for (uint i = 0; i < formatCount; i++) {
            if (formats[i].format == VK_FORMAT_B8G8R8A8_UNORM && formats[i].colorSpace == VK_COLOR_SPACE_SRGB_NONLINEAR_KHR) {
                chosenFormat = formats[i];
                break;
            }
        }
    }
    free(formats);
    return chosenFormat;
}

VkPresentModeKHR choose_swap_present_mode(VkPhysicalDevice physicalDevice, VkSurfaceKHR surface) {
    uint presentModeCount;
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
    VkPresentModeKHR chosenPresentMode = VK_PRESENT_MODE_FIFO_KHR; // Default to FIFO mode
    for (uint i = 0; i < presentModeCount; i++) {
        if (presentModes[i] == VK_PRESENT_MODE_MAILBOX_KHR) {
            chosenPresentMode = VK_PRESENT_MODE_MAILBOX_KHR;
            zox_log_vulkan(" + present mode chose [%i]\n", i)
            break;
        }
    }
    free(presentModes);
    return chosenPresentMode;
}

void log_swap_chain_create_info(const VkSwapchainCreateInfoKHR *createInfo) {
    zox_log_vulkan("Swap Chain Create Info:\n");
    zox_log_vulkan("  sType: %d\n", createInfo->sType);
    zox_log_vulkan("  surface: %p\n", (void*)createInfo->surface);
    zox_log_vulkan("  minImageCount: %u\n", createInfo->minImageCount);
    zox_log_vulkan("  imageFormat: %d\n", createInfo->imageFormat);
    zox_log_vulkan("  imageColorSpace: %d\n", createInfo->imageColorSpace);
    zox_log_vulkan("  imageExtent.width: %u\n", createInfo->imageExtent.width);
    zox_log_vulkan("  imageExtent.height: %u\n", createInfo->imageExtent.height);
    zox_log_vulkan("  imageArrayLayers: %u\n", createInfo->imageArrayLayers);
    zox_log_vulkan("  imageUsage: %u\n", createInfo->imageUsage);
    zox_log_vulkan("  imageSharingMode: %d\n", createInfo->imageSharingMode);
    zox_log_vulkan("  compositeAlpha: %u\n", createInfo->compositeAlpha);
    zox_log_vulkan("  clipped: %u\n", createInfo->clipped);
    zox_log_vulkan("  oldSwapchain: %p\n", (void*)createInfo->oldSwapchain);
    zox_log_vulkan("  preTransform: %u\n", createInfo->preTransform);
    zox_log_vulkan("  presentMode: %u\n", createInfo->presentMode);
}

VkSurfaceCapabilitiesKHR get_vulkan_surface_capabilities() {
    VkSurfaceCapabilitiesKHR surface_capabilities;
    vkGetPhysicalDeviceSurfaceCapabilitiesKHR(vk_physical_device, *vk_surface, &surface_capabilities);
    vk_swap_chain_extent = surface_capabilities.currentExtent;
    // vk_images_count = surface_capabilities.minImageCount  + 1;
    zox_log_vulkan(" > surace images count: %i\n", (surface_capabilities.minImageCount + 1))
    return surface_capabilities;
}

byte create_vulkan_swap_chain() {
    VkBool32 presentSupport = VK_FALSE;
    vkGetPhysicalDeviceSurfaceSupportKHR(vk_physical_device, queue_family_index, *vk_surface, &presentSupport);
    if (!presentSupport) return EXIT_FAILURE;
    VkSurfaceCapabilitiesKHR surface_capabilities = get_vulkan_surface_capabilities();
    VkPresentModeKHR present_mode = choose_swap_present_mode(vk_physical_device, *vk_surface);
    VkSurfaceFormatKHR surface_format = choose_surface_format(vk_physical_device, *vk_surface);
    // create swap chain here
    VkSwapchainCreateInfoKHR createInfo = { };
    createInfo.sType = VK_STRUCTURE_TYPE_SWAPCHAIN_CREATE_INFO_KHR;
    createInfo.imageArrayLayers = 1;
    createInfo.imageUsage = VK_IMAGE_USAGE_COLOR_ATTACHMENT_BIT;
    createInfo.imageSharingMode = VK_SHARING_MODE_EXCLUSIVE; // Depends on queue family setup
    createInfo.compositeAlpha = VK_COMPOSITE_ALPHA_OPAQUE_BIT_KHR;
    createInfo.clipped = VK_TRUE;
    createInfo.oldSwapchain = VK_NULL_HANDLE;
    createInfo.surface = *vk_surface;
    createInfo.imageFormat = surface_format.format;
    createInfo.minImageCount = vk_images_count;
    createInfo.imageExtent = vk_swap_chain_extent;
    createInfo.imageColorSpace = surface_format.colorSpace;
    createInfo.preTransform = surface_capabilities.currentTransform;
    createInfo.presentMode = present_mode;
    // log_swap_chain_create_info(&createInfo);
    VkResult swapChainResults = vkCreateSwapchainKHR(vk_device, &createInfo, NULL, &vk_swap_chain);
    if (swapChainResults != VK_SUCCESS) {
        zox_log_vulkan(" ! failed vkCreateSwapchainKHR [%s]\n", vulkan_result_to_string(swapChainResults))
        return EXIT_FAILURE;
    }
    return EXIT_SUCCESS;
}

byte create_vulkan_images() {
    // creates swap chain images
    VkResult swapChainImagesCountResult = vkGetSwapchainImagesKHR(vk_device, vk_swap_chain, &vk_images_count, NULL);
    if (swapChainImagesCountResult != VK_SUCCESS) {
        zox_log_vulkan(" ! failed to get swap chain images\n")
        return EXIT_FAILURE;
    }
    zox_log_vulkan(" > getting swap chain images: %i\n", vk_images_count)
    VkImage* vk_swap_chain_images = malloc(vk_images_count * sizeof(VkImage));
    if (vk_swap_chain_images == NULL) {
        zox_log_vulkan(" ! vk_swap_chain_images is null\n")
        return EXIT_FAILURE;
    }
    VkResult swapChainImagesResult = vkGetSwapchainImagesKHR(vk_device, vk_swap_chain, &vk_images_count, vk_swap_chain_images);
    if (swapChainImagesResult != VK_SUCCESS) {
        zox_log_vulkan(" ! failed to get swap chain images [%s]\n", vulkan_result_to_string(swapChainImagesResult))
        free(vk_swap_chain_images);
        return EXIT_FAILURE;
    }
    // image view
    VkImageViewCreateInfo viewCreateInfo = {};
    viewCreateInfo.sType = VK_STRUCTURE_TYPE_IMAGE_VIEW_CREATE_INFO;
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
    vk_image_views = malloc(sizeof(VkImageView) * vk_images_count);
    for (int i = 0; i < vk_images_count; i++) {
        viewCreateInfo.image = vk_swap_chain_images[i];
        VkResult imageViewResult = vkCreateImageView(vk_device, &viewCreateInfo, NULL, &vk_image_views[i]);
        if (imageViewResult != VK_SUCCESS) {
            zox_log_vulkan(" ! failed to create image view [%s]\n", vulkan_result_to_string(imageViewResult))
            free(vk_swap_chain_images);
            return EXIT_FAILURE;
        }
    }
    free(vk_swap_chain_images);
    return EXIT_SUCCESS;
}

byte create_vulkan_frame_buffer(VkImageView *vk_image_views) {
    // For simplicity, assuming a single imageView (in a real scenario, you'd loop over all swap chain images)
    // Create Framebuffer
    VkFramebufferCreateInfo framebufferInfo = {};
    framebufferInfo.sType = VK_STRUCTURE_TYPE_FRAMEBUFFER_CREATE_INFO;
    framebufferInfo.renderPass = vk_render_pass;
    framebufferInfo.attachmentCount = 1;
    framebufferInfo.width = vk_swap_chain_extent.width;
    framebufferInfo.height = vk_swap_chain_extent.height;
    framebufferInfo.layers = 1;
    vk_frame_buffers = malloc(sizeof(VkFramebuffer) * vk_images_count);
    for (int i = 0; i < vk_images_count; i++) {
        VkImageView attachments[] = { vk_image_views[i] };
        framebufferInfo.pAttachments = attachments;
        // creates vk_frame_buffer
        VkResult framebufferResult = vkCreateFramebuffer(vk_device, &framebufferInfo, NULL, &vk_frame_buffers[i]);
        if (framebufferResult != VK_SUCCESS) {
            zox_log_vulkan(" ! failed to create framebuffer [%s]\n", vulkan_result_to_string(framebufferResult))
            // Cleanup and exit logic
            return EXIT_FAILURE;
        }
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

byte create_vulkan_debugger() {
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

byte create_vulkan_pipeline(ecs_world_t *world, VkInstance* vk_instance, VkSurfaceKHR* vk_surface) {
    // int width, height;
    // SDL_Vulkan_GetDrawableSize(window, &width, &height);
    int2 screen_size = get_screen_size();
    vk_swap_chain_extent = (VkExtent2D) { screen_size.x, screen_size.y };

    //if (create_vulkan_debugger() == EXIT_FAILURE) return EXIT_FAILURE;
    //zox_log_vulkan(" > success creating vulkan debugger\n")

    if (vulkan_create_device() == EXIT_FAILURE) return EXIT_FAILURE;
    zox_log_vulkan(" > success creating vulkan device\n")

    vkGetDeviceQueue(vk_device, queue_family_index, 0, &graphics_queue);

    if (vulkan_create_command_buffer() == EXIT_FAILURE) return EXIT_FAILURE;
    zox_log_vulkan(" > success creating vulkan command_buffer\n")

    // Swap Chain Extent
    if (create_vulkan_render_pass() == EXIT_FAILURE) return EXIT_FAILURE;
    zox_log_vulkan(" > success creating vulkan render_pass\n")

    if (create_vulkan_swap_chain() == EXIT_FAILURE) return EXIT_FAILURE;
    zox_log_vulkan(" > success creating vulkan swap_chain\n")

    if (create_vulkan_images() == EXIT_FAILURE) return EXIT_FAILURE;
    zox_log_vulkan(" > success creating vulkan images\n")

    if (create_vulkan_frame_buffer(vk_image_views) == EXIT_FAILURE) return EXIT_FAILURE;
    zox_log_vulkan(" > success creating vulkan frame_buffer\n")

    VkSemaphoreCreateInfo semaphoreInfo = { };
    semaphoreInfo.sType = VK_STRUCTURE_TYPE_SEMAPHORE_CREATE_INFO;
    VkResult sepaphoreResult = vkCreateSemaphore(vk_device, &semaphoreInfo, NULL, &vk_semaphore);
    if (sepaphoreResult != VK_SUCCESS) {
        zox_log_vulkan(" ! failed to vk_semaphore [%s]\n", vulkan_result_to_string(sepaphoreResult))
        return EXIT_FAILURE;
    }

    VkResult semaphoreImageResult = vkCreateSemaphore(vk_device, &semaphoreInfo, NULL, &vk_semaphore_image);
    if (semaphoreImageResult != VK_SUCCESS) {
        zox_log_vulkan(" ! failed to create vk_semaphore_image [%s]\n", vulkan_result_to_string(semaphoreImageResult));
        return EXIT_FAILURE;
    }

    // create our fence
    VkFenceCreateInfo fenceInfo = {};
    fenceInfo.sType = VK_STRUCTURE_TYPE_FENCE_CREATE_INFO;
    vkCreateFence(vk_device, &fenceInfo, NULL, &vk_fence);
    return EXIT_SUCCESS;
}

    // get queues
    /*uint queueFamilyCount = 0;
    vkGetPhysicalDeviceQueueFamilyProperties(vk_physical_device, &queueFamilyCount, NULL);
    VkQueueFamilyProperties queueFamilies[queueFamilyCount];
    vkGetPhysicalDeviceQueueFamilyProperties(vk_physical_device, &queueFamilyCount, queueFamilies);
    VkBool32 presentSupport = VK_FALSE;
    int presentQueueFamilyIndex = -1;
    for (uint i = 0; i < queueFamilyCount; i++) {
        vkGetPhysicalDeviceSurfaceSupportKHR(vk_physical_device, i, *vk_surface, &presentSupport);
        if (queueFamilies[i].queueFlags & VK_QUEUE_GRAPHICS_BIT && presentSupport) {
            presentQueueFamilyIndex = i;
            break;
        }
    }*/
    // vkGetDeviceQueue(vk_device, presentQueueFamilyIndex, 0, &presents_queue);
