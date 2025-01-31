// todo: let modules add onto this function with a dynamic list of function pointers
//      - need to do this for rendering, input, statistics, sdl, opengl

// forward declare types

#ifndef zox_int2
#define zox_int2
typedef struct {
    int x, y;
} int2;
#endif
#ifndef zox_float3
#define zox_float3
typedef struct {
    float x, y, z;
} float3;
#endif

extern byte headless;
extern ecs_entity_t main_app;
extern ecs_entity_t keyboard_entity;
extern int2 viewport_dimensions;
extern float3 viewport_clear_color;

extern void run_ecs(ecs_world_t *world);
extern void device_reset_keyboard(ecs_world_t *world, const ecs_entity_t keyboard_entity);
extern void update_sdl(ecs_world_t *world, const ecs_entity_t e, const int2 viewport_size);
extern void opengl_clear_viewport_all(const float3 clear_color);
extern void iterate_time(ecs_world_t *world);
extern void app_update_gpu(ecs_world_t *world);

void update_core(ecs_world_t *world) {
    if (!headless) {
        device_reset_keyboard(world, keyboard_entity);
        update_sdl(world, main_app, viewport_dimensions);
        #ifdef zoxel_on_web
            update_web_canvas(world);   // handles resize event
        #endif
        opengl_clear_viewport_all(viewport_clear_color); // theres only one frame buffer for each app
    }
    run_ecs(world);
    iterate_time(world);
    if (!headless) {
        app_update_gpu(world);
    }
    #ifdef zoxel_log_frame_ms
    zox_log(" > frame time [%fms]\n", (float) (zox_delta_time * 1000.0f))
    #endif
}
