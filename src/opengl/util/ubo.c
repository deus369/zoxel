int zox_get_max_ubo_size() {
    GLint max_ubo_bytes = 0;
    glGetIntegerv(GL_MAX_UNIFORM_BLOCK_SIZE, &max_ubo_bytes);
    // mat4 = 16 floats = 64 bytes
    return max_ubo_bytes / (sizeof(float) * 16);
}

int zox_get_safe_ubo_size() {
#ifdef zox_android
    return 256; // or query if EGL/OpenGL ES 3.0+ supports glGetIntegerv
#else
    return int_min(10000, zox_get_max_ubo_size());
#endif
}