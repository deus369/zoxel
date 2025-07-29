

double get_ram_use() {
    double ram_use = 0; // RAM use in bytes
    // Open /proc/self/statm to get memory information of the current process
    FILE *statm = fopen("/proc/self/statm", "r");
    if (statm == NULL) {
        perror("fopen");
        return 0;
    }
    // Read the resident set size (RSS) from /proc/self/statm
    unsigned long size, resident, share, text, lib, data, dt;
    if (fscanf(statm, "%lu %lu %lu %lu %lu %lu %lu", &size, &resident, &share, &text, &lib, &data, &dt) != 7) {
        perror("fscanf");
        fclose(statm);
        return 0;
    }
    // Close the file
    fclose(statm);
    // Get the page size in bytes
#ifdef zox_linux
    long page_size = sysconf(_SC_PAGESIZE);
    if (page_size == -1) {
        perror("sysconf");
        return 0;
    }
    // Calculate RAM usage in bytes
    ram_use = resident * page_size;
#endif
    return ram_use;
}

double get_integrated_gpu_memory_total() {
    double gpu_memory_total = 0;
    FILE *fp;
    char path[1035];
    char command[] = "lshw -C display | grep size";
    // Open the command for reading.
    fp = popen(command, "r");
    if (fp == NULL) {
        perror("popen");
        return 0;
    }
    // Read the output a line at a time - output it.
    while (fgets(path, sizeof(path), fp) != NULL) {
        // Assuming the output format contains something like "size: 2048MiB"
        char *size_str = strstr(path, "size:");
        if (size_str != NULL) {
            size_str += 5; // Move past "size: "
            gpu_memory_total = atof(size_str);
            break;
        }
    }
    // Close the command.
    pclose(fp);
    // Convert MiB to bytes
    // gpu_memory_total *= 1024 * 1024;
    return gpu_memory_total;
}

 char* get_byte_type(double *bytes) {
    // if in mb -  / (1024 * 1024
    char *byte_type;
    if (*bytes < 1024.0) {
        byte_type = "b";
    } else if (*bytes < 1024 * 1024.0) {
        byte_type = "kb";
        *bytes /= 1024.0;
    } else if (*bytes < 1024 * 1024 * 1024.0) {
        byte_type = "mb";
        *bytes /= 1024 * 1024.0;
    } else if (*bytes < 1024 * 1024 * 1024 * 1024.0) {
        byte_type = "gb";
        *bytes /= 1024 * 1024 * 1024.0;
    } else {
        byte_type = "tb";
        *bytes /= 1024 * 1024 * 1024 * 1024.0;
    }
    return byte_type;
}

char* get_byte_type_lu(uint64_t bytes) {
    char *byte_type;
    if (bytes < 1024.0) {
        byte_type = "b";
    } else if (bytes < 1024 * 1024) {
        byte_type = "kb";
    } else if (bytes < 1024 * 1024 * 1024) {
        byte_type = "mb";
    } else {
        byte_type = "gb";
    }
    return byte_type;
}

double get_bytes_double_as_unit(uint64_t bytes) {
    if (bytes < 1024.0) {
        return ((double) bytes);
    } else if (bytes < 1024 * 1024) {
        return ((double) bytes) / 1024.0;
    } else if (bytes < 1024 * 1024 * 1024) {
        return ((double) bytes) / (1024.0 * 1024.0);
    } else {
        return ((double) bytes) / (1024.0 * 1024.0 * 1024.0);
    }
}

int debug_system(char buffer[], int buffer_size, int buffer_index) {
    double ram_used = get_ram_use(); // ram use in bytes
    char *byte_type = get_byte_type(&ram_used);
    buffer_index += snprintf(buffer + buffer_index, buffer_size - buffer_index, "ram [%.00f%s]\n", ram_used, byte_type);

    uint64_t gpu_memory_used = get_amd_gpu_memory_used(); // ram use in megabytes
    uint64_t gpu_memory_total = get_amd_gpu_memory_total(); // ram use in megabytes
    char *byte_type2 = get_byte_type_lu(gpu_memory_used);
    char *byte_type3 = get_byte_type_lu(gpu_memory_total);
    double gpu_memory_used_d = get_bytes_double_as_unit(gpu_memory_used);
    double gpu_memory_total_d = get_bytes_double_as_unit(gpu_memory_total);

    buffer_index += snprintf(buffer + buffer_index, buffer_size - buffer_index, "gpu ram [%f%s] / [%f%s]\n", gpu_memory_used_d, byte_type2, gpu_memory_total_d, byte_type3);

    return buffer_index;
}
