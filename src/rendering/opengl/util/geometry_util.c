unsigned char does_support_geometry_shaders() {
    GLint maxGeometryOutputVertices;
    glGetIntegerv(GL_MAX_GEOMETRY_OUTPUT_VERTICES, &maxGeometryOutputVertices);
    return (maxGeometryOutputVertices > 0);
}

void check_geometry() {
#ifdef zox_print_shader_support
    if (does_support_geometry_shaders()) zox_log(" + geometry shader supported\n")
    else zox_log(" ! geometry shader unsupported\n")
#endif
}
