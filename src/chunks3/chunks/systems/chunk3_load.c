bool file_exists(const char *path) {
    struct stat buffer;
    return stat(path, &buffer) == 0;
}

byte load_voxel_node(ecs* world, FILE* in, VoxelNode* node) {
    if (fread(&node->value, sizeof(byte), 1, in) != 1) {
        zox_log("[load_voxel_node:1] read error.");
        return 0;
    }

    byte has_children = 0;
    if (fread(&has_children, sizeof(byte), 1, in) != 1) {
        zox_log("[load_voxel_node:2] read error.");
        return 0;
    }

    if (has_children) {
        if (!has_children_VoxelNode(node)) {
            open_VoxelNode(node);
        }
        VoxelNode* children = (VoxelNode*) node->ptr;
        for (int i = 0; i < 8; i++) {
            load_voxel_node(world, in, &children[i]);
        }
    } else {
        if (has_children_VoxelNode(node)) {
            close_VoxelNode(world, node);
        }
    }
    return 1;
}

// returns 1 if loaded
byte load_chunk(
    ecs *world,
    const int3 position,
    VoxelNode* node
) {
    char filename[128];
    get_chunk_filename(filename, position);
    // sprintf(filename, "chunk_%i_%i_%i.dat", position.x, position.y, position.z);
    char path[io_path_size];
    get_save_filepath(game_name, filename, path, sizeof(path));
    if (!file_exists(path)) {
        return 0;
    }
    // check if file exist
    FILE* file = fopen(path, "rb");
    if (!file) {
        zox_log_error("Failed to open filepath [%s]", path);
        return 0;
    }
    // zox_log("Loading chunk from file: %s", path);
    write_lock_VoxelNode(node);
    byte success = load_voxel_node(world, file, node);
    write_unlock_VoxelNode(node);
    if (fclose(file) != 0) {
        zox_log_error("Failed to close file: %s", path);
    }
    return success;
}

void Chunk3LoadSystem(iter *it) {
    zox_sys_world();    // used when closing possible nodes
    zox_sys_begin();
    zox_sys_in(RenderDistanceDirty);
    zox_sys_in(ChunkPosition);
    zox_sys_out(VoxelNodeDirty);
    zox_sys_out(VoxelNodeEdited);
    zox_sys_out(VoxelNodeLoaded);
    zox_sys_out(VoxelNode);
    zox_sys_out(NodeDepth);
    for (int i = 0; i < it->count; i++) {
        zox_sys_i(RenderDistanceDirty, render_distance_dirty);
        zox_sys_i(ChunkPosition, position);
        zox_sys_o(VoxelNodeDirty, dirty);
        zox_sys_o(VoxelNodeEdited, edited);
        zox_sys_o(VoxelNodeLoaded, loaded);
        zox_sys_o(VoxelNode, node);
        zox_sys_o(NodeDepth, depth);
        if (render_distance_dirty->value != zox_dirty_active || loaded->value) {
            continue; // these shouldn't be here
        }
        if (load_chunk(world, position->value, node)) {
            loaded->value = 1;
            edited->value = 1;
            dirty->value = 1;
            depth->value = terrain_depth;
        }

    }
} zox_declare_system(Chunk3LoadSystem)