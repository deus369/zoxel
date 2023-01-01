const double frame_rate_update_speed = 1.0;
int frames_per_second = 0;
int frames_count;
double time_passed = 0.0;
double fps_delta_time = 0.0;

//! Iterate in main thread
void iterate_fps_time()
{
    frames_count++;
    time_passed += fps_delta_time;
    if (time_passed >= 1.0)
    {
        time_passed -= 1.0;
        frames_per_second = frames_count;
        frames_count = 0;
        #ifdef zoxel_log_frames_per_second
            zoxel_log("frames_per_second [%i]\n", frames_per_second);
        #endif
    }
}

//! Every noise_animation_speed it makes the update.
void FpsDisplaySystem(ecs_iter_t *it)
{
    const unsigned char number_0_start = 60;
    double delta_time = it->delta_time;
    fps_delta_time = delta_time;
    FPSDisplayTicker *fpsDisplayTickers = ecs_field(it, FPSDisplayTicker, 1);
    ZextDirty *zextDirtys = ecs_field(it, ZextDirty, 2);
    ZextData *zextDatas = ecs_field(it, ZextData, 3);
    unsigned char changed = 0;   //! Skip changes if isn't updated.
    for (int i = 0; i < it->count; i++)
    {
        FPSDisplayTicker *fpsDisplayTicker = &fpsDisplayTickers[i];
        fpsDisplayTicker->value -= delta_time;
        if (fpsDisplayTicker->value <= 0.0)
        {
            // printf("Checking FPS Ticker Ticked.\n");
            fpsDisplayTicker->value += frame_rate_update_speed;
            if (fpsDisplayTicker->value <= -frame_rate_update_speed)
            {
                fpsDisplayTicker->value = 0;
            }
            ZextDirty *zextDirty = &zextDirtys[i];
            if (zextDirty->value == 0)
            {
                zextDirty->value = 1;
                // printf("Updated FPSDisplay.\n");
                ZextData *zextData = &zextDatas[i];
                if (frames_per_second < 10)
                {
                    zextData->value[0] = number_0_start;
                    zextData->value[1] = number_0_start;
                    zextData->value[2] = number_0_start + frames_per_second;
                }
                else if (frames_per_second < 100)
                {
                    zextData->value[0] = number_0_start;
                    zextData->value[1] = number_0_start + (frames_per_second / 10);
                    zextData->value[2] = number_0_start + (frames_per_second % 10);
                }
                else if (frames_per_second < 1000)
                {
                    zextData->value[0] = number_0_start + (frames_per_second / 100);
                    zextData->value[1] = number_0_start + (frames_per_second / 10) % 10;
                    zextData->value[2] = number_0_start + ((frames_per_second % 100) % 10);
                }
                else // if (frames_per_second < 100)
                {
                    zextData->value[0] = number_0_start;
                    zextData->value[1] = number_0_start;
                    zextData->value[2] = number_0_start;
                }
                /*for (int j = 0; j < zextData->length; j++)
                {
                    zextData->value[j] = 60 + rand() % 10;
                }*/
                changed = 1;
                // printf("AnimateNoiseSystem, GenerateTexture Triggered: [%lu] on index [%i]\n", (long int)(it->entities[i]), i);
            }
        }
    }
    if (!changed)
    {
        ecs_query_skip(it);
    }
}
zoxel_declare_system(FpsDisplaySystem)