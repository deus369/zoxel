extern ecs_entity_t spawn_line2D(ecs_world_t *world, float2 pointA, float2 pointB, float thickness, double life_time);

void SoundDebugSystem(ecs_iter_t *it) {
    if (!zox_visualize_sounds) {
        return;
    }
//#ifdef zox_mod_lines2D
    zox_sys_world()
    byte has_begun = 0;
    zox_sys_begin()
    zox_sys_in(SoundData)
    zox_sys_in(TriggerSound)
    for (int i = 0; i < it->count; i++) {
        zox_sys_i(TriggerSound, triggerSound)
        zox_sys_i(SoundData, soundData)
        if (triggerSound->value != zox_sound_play_run) {
            continue;
        }
        const double decay_time = soundData->length / sample_rate_f; // 6.0 + rand() % 6;
        if (!has_begun) {   // draw axis
            has_begun = 1;
            const float line_length = 1.0f;
            spawn_line2D(world, (float2) { -line_length, 0 }, (float2) { line_length, 0 }, 3.0f, decay_time);
            spawn_line2D(world, (float2) { -line_length, -line_length }, (float2) { -line_length, line_length }, 6.0f, decay_time);
        }
        int start_position = sound_display_start * soundData->length;
        int end_position = sound_display_end * soundData->length;
        int total_displaying = end_position - start_position;
        for (int i = start_position; i < end_position; i += sound_display_skip_rate) {
            float x_position = (i - start_position) / (float) total_displaying;
            // float x_position = (float) i / (float) soundData->length;
            x_position *= 2.0f;
            x_position -= 1.0f;
            spawn_line2D(world, (float2) { x_position, 0 }, (float2) { x_position, soundData->value[i] }, debug_sound_thickness, decay_time);
        }
    }
//#endif
} zox_declare_system(SoundDebugSystem)