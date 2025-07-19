extern float viewport_scale;

static inline void zox_gpu_line_thickness(const float thickness) {
    glLineWidth(thickness * viewport_scale);
}

static inline void zox_gpu_render_lines(uint length) {
    glDrawArrays(GL_LINES, 0, length);
}