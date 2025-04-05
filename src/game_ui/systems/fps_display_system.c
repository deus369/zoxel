void FpsDisplaySystem(ecs_iter_t *it) {
    const double frame_rate_update_speed = 1.0;
    const byte number_0_start = 60;
    init_delta_time()
    zox_field_out(TextData, textDatas, 2)
    zox_field_out(ZextDirty, zextDirtys, 3)
    zox_field_out(FPSDisplayTicker, fpsDisplayTickers, 4)
    for (int i = 0; i < it->count; i++) {
        zox_field_o(ZextDirty, zextDirtys, zextDirty)
        if (zextDirty->value) continue;
        zox_field_o(FPSDisplayTicker, fpsDisplayTickers, fpsDisplayTicker)
        fpsDisplayTicker->value -= delta_time;
        if (fpsDisplayTicker->value <= 0) {
            fpsDisplayTicker->value += frame_rate_update_speed;
            if (fpsDisplayTicker->value <= -frame_rate_update_speed) fpsDisplayTicker->value = 0;
            zox_field_o(TextData, textDatas, textData)
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
