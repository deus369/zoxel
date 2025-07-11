char* zox_read_shader(const char *filepath) {
    FILE *file = fopen(filepath, "rb");
    if (!file) {
        return NULL;
    }
    fseek(file, 0, SEEK_END);
    long size = ftell(file);
    rewind(file);
    char *buffer = malloc(size + 1);
    if (!buffer) {
        fclose(file);
        return NULL;
    }
    size_t read_bytes = fread(buffer, 1, size, file);
    if (read_bytes != (size_t) size) {
        free(buffer);
        fclose(file);
        return NULL;
    }
    buffer[size] = '\0'; // null terminate exactly here
    fclose(file);
    return buffer;
}

static inline ecs_entity_t spawn_file_shader_at_path(ecs_world_t *world, const ecs_entity_t prefab, const char* path) {
    return spawn_file_shader(world, prefab, zox_read_shader(path));
}