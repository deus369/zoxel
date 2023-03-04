//! The main update loop.
void update_core()
{
    // apps / Input events
    if (!headless)
    {
        reset_input_devices(world);
        update_sdl(world);
        #ifdef WEB_BUILD
        update_web_canvas(world);   // handles resize event
        #endif
        render_pre_loop();
    }
    // ecs_log_set_level(1);    // use this to debug system pipelines
    ecs_progress(world, 0);
    // main thread, generates gpu buffer
    if (!headless)
    {
        set_mouse_mode();
        render_loop_temp();
    }
}

int begin_core(int argc, char* argv[])
{
    int didFail = process_arguments(argc, argv);
    if (didFail == EXIT_FAILURE)
    {
        return EXIT_SUCCESS;
    }
    int cpuCoreCount = SDL_GetCPUCount();
    open_ecs(argc, argv, profiler, cpuCoreCount); // begin ecs
    return 0;
}

void close_core()
{
    close_ecs();
    if (!headless)
    {
        dispose_opengl();
        SDL_Quit();
    }
}