

byte zox_memory_check(const void* ptr, size_t size) {
    uintptr_t addr = (uintptr_t)ptr;

    // Typical user-space lower bound check
    if (addr < 0x1000) {
        return 0;
    }

    // Optional: upper bound guard (exclude kernel space or crazy high addresses)
    if (addr + size > 0x00007fffffffffff) {
        return 0;
    }

    // Passes heuristic range check
    return 1;
}

byte is_valid_voxel_node(const VoxelNode* node) {
    if (!node) {
        return 0;
    }

    uintptr_t addr = (uintptr_t)node;

    // First, verify the memory is actually readable before we deref ANY fields
    if (!zox_memory_check((void*)node, sizeof(VoxelNode))) {
        zox_log_error("VoxelNode pointer invalid or out of range: 0x%zx", addr);
        return 0;
    }

    // Check value field directly, now it's safe
    if (node->value > 255) {
        zox_log_error("VoxelNode value overflow: %u", node->value);
        return 0;
    }

    // Only now, *after* we validated the base node, call has_children
    byte has_kids = has_children_VoxelNode(node);
    if (has_kids) {
        VoxelNode* kids = get_children_VoxelNode(node);
        if (!kids || !zox_memory_check(kids, sizeof(VoxelNode) * 8)) {
            zox_log_error("VoxelNode children pointer invalid or corrupt: 0x%zx", (uintptr_t)kids);
            return 0;
        }
    }

    return 1;
}
