// sudo apt install rocm-smi librocm-smi-dev
#ifdef zox_lib_amd

#include <rocm_smi/rocm_smi.h>
byte amd_initialized = 0;

void initialize_amd() {
    rsmi_status_t result;
    uint32_t device_count;
    // Initialize the ROCm SMI library
    result = rsmi_init(0);
    if (result == RSMI_STATUS_SUCCESS) {
        // Get the number of devices
        result = rsmi_num_monitor_devices(&device_count);
        if (result == RSMI_STATUS_SUCCESS) {
            amd_initialized = 1;
            // zox_log(" + amd initialized [%i]\n", device_count)
        }
    }
}

void dispose_amd() {
    if (amd_initialized) {
        amd_initialized = 0;
        rsmi_shut_down();
    }
}

uint64_t get_amd_gpu_memory_used() {
    if (!amd_initialized) return 0;
    rsmi_status_t result;
    uint64_t used_memory;
    result = rsmi_dev_memory_usage_get(0, RSMI_MEM_TYPE_VRAM, &used_memory);
    if (result != RSMI_STATUS_SUCCESS) return 0;
    return used_memory;
}

uint64_t get_amd_gpu_memory_total() {
    if (!amd_initialized) return 0;
    rsmi_status_t result;
    uint64_t total_memory;
    result = rsmi_dev_memory_total_get(0, RSMI_MEM_TYPE_VRAM, &total_memory);
    if (result != RSMI_STATUS_SUCCESS) return 0;
    return total_memory;
}

#else

void initialize_amd() { }

void dispose_amd() { }

uint64_t get_amd_gpu_memory_used() { return 0; }

uint64_t get_amd_gpu_memory_total() { return 0; }

#endif
