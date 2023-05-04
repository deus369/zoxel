void FpsDisplaySystem(ecs_iter_t *it) {
    // zoxel_log("target fps %i\n", it->world->target_fps);
    const unsigned char number_0_start = 60;
    double delta_time = zoxel_delta_time; // it->delta_time;
    // zoxel_delta_time = delta_time; // delta_time; // it->delta_system_time;
    FPSDisplayTicker *fpsDisplayTickers = ecs_field(it, FPSDisplayTicker, 1);
    ZextDirty *zextDirtys = ecs_field(it, ZextDirty, 2);
    ZextData *zextDatas = ecs_field(it, ZextData, 3);
    unsigned char changed = 0;   //! Skip changes if isn't updated.
    for (int i = 0; i < it->count; i++) {
        FPSDisplayTicker *fpsDisplayTicker = &fpsDisplayTickers[i];
        fpsDisplayTicker->value -= delta_time;
        if (fpsDisplayTicker->value <= 0.0) {
            changed = 1;
            // printf("Checking FPS Ticker Ticked.\n");
            ZextDirty *zextDirty = &zextDirtys[i];
            zextDirty->value = 1;
            fpsDisplayTicker->value += frame_rate_update_speed;
            if (fpsDisplayTicker->value <= -frame_rate_update_speed) {
                fpsDisplayTicker->value = 0;
            }
            // printf("Updated FPSDisplay.\n");
            ZextData *zextData = &zextDatas[i];
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
            /*for (int j = 0; j < zextData->length; j++)
            {
                zextData->value[j] = 60 + rand() % 10;
            }*/
            // printf("AnimateNoiseSystem, GenerateTexture Triggered: [%lu] on index [%i]\n", (long int)(it->entities[i]), i);
        }
    }
    if (!changed) {
        ecs_query_skip(it);
    }
}
zoxel_declare_system(FpsDisplaySystem)