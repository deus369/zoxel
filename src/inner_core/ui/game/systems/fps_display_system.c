void FpsDisplaySystem(ecs_iter_t *it) {
    const double frame_rate_update_speed = 1.0;
    const unsigned char number_0_start = 60;
    const double delta_time = zox_delta_time;
    unsigned char system_updated = 0;
    zox_field_out(ZextData, zextDatas, 2)
    zox_field_out(ZextDirty, zextDirtys, 3)
    zox_field_out(FPSDisplayTicker, fpsDisplayTickers, 4)
    for (int i = 0; i < it->count; i++) {
        zox_field_i_out(ZextDirty, zextDirtys, zextDirty)
        if (zextDirty->value) continue;
        zox_field_i_out(FPSDisplayTicker, fpsDisplayTickers, fpsDisplayTicker)
        fpsDisplayTicker->value -= delta_time;
        if (fpsDisplayTicker->value <= 0) {
            system_updated = 1;
            fpsDisplayTicker->value += frame_rate_update_speed;
            if (fpsDisplayTicker->value <= -frame_rate_update_speed) fpsDisplayTicker->value = 0;
            zox_field_i_out(ZextData, zextDatas, zextData)
            resize_memory_component(ZextData, zextData, unsigned char, 3)
            if (frames_per_second < 10) {
                zextData->value[0] = number_0_start;
                zextData->value[1] = number_0_start;
                zextData->value[2] = number_0_start + frames_per_second;
            } else if (frames_per_second < 100) {
                zextData->value[0] = number_0_start;
                zextData->value[1] = number_0_start + (frames_per_second / 10);
                zextData->value[2] = number_0_start + (frames_per_second % 10);
            } else if (frames_per_second < 1000) {
                zextData->value[0] = number_0_start + (frames_per_second / 100);
                zextData->value[1] = number_0_start + (frames_per_second / 10) % 10;
                zextData->value[2] = number_0_start + ((frames_per_second % 100) % 10);
            } else {
                zextData->value[0] = number_0_start;
                zextData->value[1] = number_0_start;
                zextData->value[2] = number_0_start;
            }
            zextDirty->value = 1;
        }
    }
#ifndef zoxel_on_windows
    if (!system_updated) ecs_query_skip(it);   // skip changes if isn't updated
#endif
} zox_declare_system(FpsDisplaySystem)
