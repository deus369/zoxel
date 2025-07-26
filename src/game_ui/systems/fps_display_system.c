void FpsDisplaySystem(ecs_iter_t *it) {
    const double frame_rate_update_speed = 1.0;
    const byte number_0_start = 60;
    init_delta_time()
    zox_sys_begin()
    zox_sys_out(TextData)
    zox_sys_out(ZextDirty)
    zox_sys_out(FPSDisplayTicker)
    for (int i = 0; i < it->count; i++) {
        zox_sys_o(ZextDirty, zextDirty)
        zox_sys_o(FPSDisplayTicker, fpsDisplayTicker)
        zox_sys_o(TextData, textData)
        fpsDisplayTicker->value -= delta_time;
        if (zextDirty->value) {
            continue;
        }
        if (fpsDisplayTicker->value <= 0) {
            fpsDisplayTicker->value += frame_rate_update_speed;
            if (fpsDisplayTicker->value <= -frame_rate_update_speed) {
                fpsDisplayTicker->value = 0;
            }
            resize_memory_component(TextData, textData, byte, 3)
            if (frames_per_second < 10) {
                textData->value[0] = number_0_start;
                textData->value[1] = number_0_start;
                textData->value[2] = number_0_start + frames_per_second;
            } else if (frames_per_second < 100) {
                textData->value[0] = number_0_start;
                textData->value[1] = number_0_start + (frames_per_second / 10);
                textData->value[2] = number_0_start + (frames_per_second % 10);
            } else if (frames_per_second < 1000) {
                textData->value[0] = number_0_start + (frames_per_second / 100);
                textData->value[1] = number_0_start + (frames_per_second / 10) % 10;
                textData->value[2] = number_0_start + ((frames_per_second % 100) % 10);
            } else {
                textData->value[0] = number_0_start;
                textData->value[1] = number_0_start;
                textData->value[2] = number_0_start;
            }
            zextDirty->value = 1;
        }
    }
} zox_declare_system(FpsDisplaySystem)
