void init_zems() { }

void free_zems() { }

void* zalloc(uint length) {
    return malloc(length);
}

void zee(void* ptr) {
    free(ptr);
}

void* rezalloc(void* ptr, uint new_length) {
    return realloc(ptr, new_length);
}
