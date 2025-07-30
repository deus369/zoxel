static inline ecs_entity_t spawn_file_shader_at_path(ecs_world_t *world,
    const ecs_entity_t prefab,
    const char* path)
{
    char* source = zox_read_shader(path);
    if (!source) {
        return 0;
    }
    byte shader_include_es = is_shaders_es; // opengl_mode == zox_opengl_es;
    int ubo_size = zox_get_safe_ubo_size();

    // zox_log("+ shader processing with ver [%i] es [%s] ubo_size [%i]", shader_opengl_version, (shader_include_es ? "es" : ""), ubo_size);
    // zox_log(" - source [%s]\n%s", path, source)
    // zox_log("-------------------------------")

    // Example: #version 320 es
    char* versioned_source = append_shader_version(source, shader_opengl_version, shader_include_es);
    free(source);

    if (!versioned_source) {
        zox_log_error("[versioned_source] is invalid")
        return 0;
    }

    char* processed_source = process_ubo_max_define(versioned_source, ubo_size);
    free(versioned_source);

    if (!processed_source) {
        zox_log_error("[processed_source] is invalid")
        return 0;
    }
    if (is_log_shaders) {
        zox_log("final source [%s]\n%s", path, processed_source)
        zox_log("-------------------------------")
    }
    return spawn_file_shader(world, prefab, processed_source);
}

void load_files_shaders(ecs_world_t *world) {
    char* load_directory = concat_file_path(resources_path, directory_shaders);
    FileList files = get_files(load_directory, 1);
    files_shaders = malloc(sizeof(ecs_entity_t) * files.count);
    files_hashmap_shaders = create_string_hashmap(files.count);
    zox_log_io(" + io loaded [shaders] [%i]", files.count)
    for (int i = 0; i < files.count; i++) {
        char* filepath = files.files[i];
        char* filename = files.filenames[i];
        zox_log_io("   - [%i] [shader] [%s]", i, filepath)
        const ecs_entity_t e = spawn_file_shader_at_path(world, prefab_file_shader, filepath);
        if (e) {
            string_hashmap_add(files_hashmap_shaders, new_string_data_clone(filename), e);
        }
        files_shaders[i] = e;
    }
    free_files(&files);
    files_count_shaders = files.count;
}

void dispose_files_shaders() {
    zox_log_io(" > disposing [%i] [shaders]", files_hashmap_shaders->size)
    string_hashmap_dispose(files_hashmap_shaders);
    files_hashmap_shaders = NULL;
    free(files_shaders);
    files_shaders = NULL;
}