// TODO: Save VoxelNode to disk when VoxelNodeDirty - realm/terrain_<ID>/chunk_id
// Later: cache save path, for now just make it
// todo: make a key that loads chunk data and refreshes for now
// TODO: Add error checks here when writing/reading

byte save_voxel_node(FILE* out, const VoxelNode* node) {
    if (!node) {
        return 1;
    }
    if (fwrite(&node->value, sizeof(byte), 1, out) != 1) {
        zox_log_error("[save_voxel_node:1] Failed to write node value.");
        return 1;
    }

    byte has_children = has_children_VoxelNode(node);
    if (fwrite(&has_children, sizeof(byte), 1, out) != 1) {
        zox_log_error("[save_voxel_node:2] Failed to write has_children.");
        return 1;
    }

    byte result = 0;
    if (has_children) {
        if (!node->ptr) {
            zox_log_error("Node has children but ptr is null!");
            return 1;
        }
        VoxelNode* children = (VoxelNode*) node->ptr;
        for (int i = 0; i < 8; i++) {
            byte error = save_voxel_node(out, &children[i]);
            if (error) {
                result = 1;
            }
        }
    }
    return result;
}

void Chunk3SaveSystem(iter *it) {
    zox_sys_begin();
    zox_sys_in(VoxelNodeEdited);
    zox_sys_in(VoxelNodeDirty);
    zox_sys_in(VoxelNode);
    zox_sys_in(ChunkPosition);
    for (int i = 0; i < it->count; i++) {
        zox_sys_i(VoxelNodeEdited, edited);
        zox_sys_i(VoxelNodeDirty, dirty);
        zox_sys_i(VoxelNode, node);
        zox_sys_i(ChunkPosition, position);
        if (dirty->value != zox_dirty_active || !edited->value) {
            continue; // these shouldn't be here
        }
        // later add id/int3 there
        char filename[128];
        get_chunk_filename(filename, position->value);
        // sprintf(filename, "chunk_%i_%i_%i.dat", position->value.x, position->value.y, position->value.z);
        char path[io_path_size];
        get_save_filepath(game_name, filename, path, sizeof(path));
        // zox_log("Saving chunk to file: %s", path);

        FILE* file = fopen(path, "wb");
        if (file == NULL) {
            zox_log_error("Error saving [%s]", path);
            continue;
        }
        read_lock_VoxelNode(node);
        save_voxel_node(file, node);
        read_unlock_VoxelNode(node);
        if (fclose(file) != 0) {
            zox_log_error("Failed to close file: %s", path);
        }
    }
} zoxd_system(Chunk3SaveSystem)