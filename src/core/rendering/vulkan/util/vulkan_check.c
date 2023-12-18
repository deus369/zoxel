#ifdef zox_include_vulkan

#include <vulkan/vulkan.h>

unsigned char is_vulkan_supported() {
    VkInstance instance;
    VkApplicationInfo appInfo = {};
    appInfo.sType = VK_STRUCTURE_TYPE_APPLICATION_INFO;
    appInfo.pApplicationName = "Vulkan Support Checker";
    appInfo.applicationVersion = VK_MAKE_VERSION(1, 0, 0);
    appInfo.pEngineName = "No Engine";
    appInfo.engineVersion = VK_MAKE_VERSION(1, 0, 0);
    appInfo.apiVersion = VK_API_VERSION_1_0;
    VkInstanceCreateInfo createInfo = {};
    createInfo.sType = VK_STRUCTURE_TYPE_INSTANCE_CREATE_INFO;
    createInfo.pApplicationInfo = &appInfo;
    if (vkCreateInstance(&createInfo, NULL, &instance) != VK_SUCCESS) {
        // printf("Vulkan is not supported on this system.\n");
        if (is_using_vulkan) is_using_vulkan = 0;
        return 0;
    } else {
        // printf("Vulkan is supported on this system.\n");
        vkDestroyInstance(instance, NULL);
        return 1;
    }
}


/*unsigned char vulkan_supported() {
    #ifdef zox_include_vulkan
        uint32_t extensionCount = 0;
        vkEnumerateInstanceExtensionProperties(NULL, &extensionCount, NULL);
        VkExtensionProperties* extensions = (VkExtensionProperties*)malloc(sizeof(VkExtensionProperties) * extensionCount);
        vkEnumerateInstanceExtensionProperties(NULL, &extensionCount, extensions);
        int surfaceExtensionSupported = 0;
        for (uint32_t i = 0; i < extensionCount; ++i) {
            if (strcmp(extensions[i].extensionName, VK_KHR_SURFACE_EXTENSION_NAME) == 0) {
                surfaceExtensionSupported = 1;
                break;
            }
        }
        free(extensions);
        if (surfaceExtensionSupported) {
            zoxel_log(" > vulkan is supported\n");
            return 1;
        } else {
            zoxel_log(" ! vulkan is not supported\n");
            return 0;
        }
    #else
        return 0;
    #endif
}*/

#else

unsigned char is_vulkan_supported() { return 0; }

#endif
