char* get_shader_source(ecs *world, char* filename) {
    const entity e = string_hashmap_get(files_hashmap_shaders, new_string_data(filename));
    if (!zox_valid(e)) {
        zox_log_error("[%s] not found", filename)
        return NULL;
    } else {
        char* source = zox_get_value(e, ShaderSource)
        if (!source) {
            zox_log_error("missing shader [%s]", filename)
        }
        return source;
    }
}