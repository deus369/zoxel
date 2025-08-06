// TODO: Save VoxelNode to disk when VoxelNodeDirty - realm/terrain_<ID>/chunk_id
// Later: cache save path, for now just make it

// todo: make a key that loads chunk data and refreshes for now

void save_voxel_node(FILE* out, const VoxelNode* node) {
    if (!node) {
        return;
    }
    fwrite(&node->value, sizeof(byte), 1, out);

    byte has_children = has_children_VoxelNode(node);
    fwrite(&has_children, sizeof(byte), 1, out);

    if (has_children) {
        VoxelNode* children = (VoxelNode*) node->ptr;
        for (int i = 0; i < 8; i++) {
            save_voxel_node(out, &children[i]);
        }
    }
}

void load_voxel_node(ecs_world_t* world, FILE* in, VoxelNode* node) {
    fread(&node->value, sizeof(byte), 1, in);

    byte has_children = 0;
    fread(&has_children, sizeof(byte), 1, in);

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
}


void Chunk3SaveSystem(ecs_iter_t *it) {
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
        sprintf(filename, "chunk_%i_%i_%i.dat", position->value.x, position->value.y, position->value.z);
        char path[io_path_size];
        get_save_filepath(game_name, filename, path, sizeof(path));
        // zox_log("Saving chunk to file: %s", path);

        FILE* file = fopen(path, "wb");
        if (file == NULL) {
            zox_log(" > error saving [%s]\n", path)
            perror("Error opening file for writing");
            continue;
        }
        read_lock_VoxelNode(node);
        save_voxel_node(file, node);
        read_unlock_VoxelNode(node);
        fclose(file);

    }
} zox_declare_system(Chunk3SaveSystem)