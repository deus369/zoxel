char* append_shader_version(
    const char* source,
    unsigned short version,
    byte is_es)
{
    if (!source || version < 100 || version > 460) {
        zox_log_error("[append_shader_version] failed, invalid inputs")
        return NULL;
    }
    // Enough for "#version 450 es\n"
    size_t length = strlen(source) + 32;
    char* new_buffer = malloc(length);
    if (!new_buffer) {
        return NULL;
    }
    snprintf(new_buffer, 32, "#version %u%s\n", version, is_es ? " es" : "");
    strcat(new_buffer, source);
    return new_buffer;
}