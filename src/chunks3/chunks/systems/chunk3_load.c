
bool file_exists(const char *path) {
    struct stat buffer;
    return stat(path, &buffer) == 0;
}

void load_chunk(
    ecs_world_t *world,
    const int3 position,
    VoxelNode* node
) {
    char filename[128];
    sprintf(filename, "chunk_%i_%i_%i.dat", position.x, position.y, position.z);
    char path[io_path_size];
    get_save_filepath(game_name, filename, path, sizeof(path));
    if (!file_exists(path)) {
        return;
    }
    // check if file exist
    FILE* file = fopen(path, "rb");
    if (!file) {
        zox_log_error("Failed to open filepath [%s]", path);
        return;
    }
    zox_log("Loading chunk from file: %s", path);
    write_lock_VoxelNode(node);
    load_voxel_node(world, file, node);
    write_unlock_VoxelNode(node);
    fclose(file);
}

void Chunk3LoadSystem(ecs_iter_t *it) {
    zox_sys_world();    // used when closing possible nodes
    zox_sys_begin();
    zox_sys_in(RenderDistanceDirty);
    zox_sys_in(ChunkPosition);
    zox_sys_out(VoxelNodeDirty);
    zox_sys_out(VoxelNodeEdited);
    zox_sys_out(VoxelNode);
    for (int i = 0; i < it->count; i++) {
        zox_sys_i(RenderDistanceDirty, render_distance_dirty);
        zox_sys_i(ChunkPosition, position);
        zox_sys_o(VoxelNodeDirty, dirty);
        zox_sys_o(VoxelNodeEdited, edited);
        zox_sys_o(VoxelNode, node);
        if (render_distance_dirty->value != zox_dirty_active || edited->value) {
            continue; // these shouldn't be here
        }
        load_chunk(world, position->value, node);
        edited->value = 1;
        dirty->value = 1;

    }
} zox_declare_system(Chunk3LoadSystem)