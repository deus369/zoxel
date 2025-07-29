char* process_ubo_max_define(const char* source, int ubo_max) {
    if (!source) return NULL;

    const char* token = "zox_ubo_max";
    size_t token_len = strlen(token);
    char ubo_max_str[32];
    snprintf(ubo_max_str, sizeof(ubo_max_str), "%d", ubo_max);

    const char* p = source;
    int count = 0;
    while ((p = strstr(p, token))) {
        count++;
        p += token_len;
    }

    if (count == 0) {
        return strdup(source);
    }

    size_t new_len = strlen(source) + count * (strlen(ubo_max_str) - token_len) + 1;
    char* result = malloc(new_len);
    if (!result) return NULL;

    const char* src = source;
    char* dst = result;
    while ((p = strstr(src, token))) {
        size_t prefix_len = p - src;
        memcpy(dst, src, prefix_len);
        dst += prefix_len;
        strcpy(dst, ubo_max_str);
        dst += strlen(ubo_max_str);
        src = p + token_len;
    }
    strcpy(dst, src); // tail
    return result;
}
