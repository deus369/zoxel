#ifdef zoxel_on_web

extern int2 screen_dimensions;  // from apps/settings
extern void on_viewport_resized(ecs_world_t *world, int2 new_screen_dimensions);

// emscripten app functions (void)
int get_canvas_width() { return 1280; }
int get_canvas_height() { return 720; }
// EM_JS(int, get_canvas_width, (), { return window.innerWidth; });
// EM_JS(int, get_canvas_height, (), { return window.innerHeight; });

int2 get_canvas_size() {
    return (int2) { get_canvas_width(), get_canvas_height() };
}

// Condensed
void resize_canvas() {
    zox_log("   > resizing canvas [%ix%i]", get_canvas_width(), get_canvas_height())
}

int2 get_webasm_screen_size() {
    int2 canvas_size = get_canvas_size();
    zox_log("   > canvas screen dimensions [%ix%i]\n", canvas_size.x, canvas_size.y)
    screen_dimensions = canvas_size;
    return canvas_size;
}

// #define debug_ui_scaling

unsigned char update_web_canvas(ecs_world_t *world) {
    int2 canvas_size = get_canvas_size();
    if (!int2_equals(screen_dimensions, canvas_size)) {
        zox_log(" > update_web_canvas: Canvas size has changed [%i x %i]\n", canvas_size.x, canvas_size.y)
        on_viewport_resized(world, (int2) { canvas_size.x, canvas_size.y });
        return 1;
    }
    return 0;
}
// }.x != canvas_size.x || screen_dimensions.y != canvas_size.y) {

#endif
