// todo: alter frequency over time during sound
void SoundProcessSystem(ecs_iter_t *it) {
    if (nosounds) {
        return;
    }
    const float default_frequency = 220; // 440;
    zox_sys_begin()
    zox_sys_in(ProcessSound)
    zox_sys_in(SoundData)
    zox_sys_in(SoundVolume)
    zox_sys_in(SoundFrequency)
    zox_sys_out(TriggerSound)
    for (int i = 0; i < it->count; i++) {
        zox_sys_i(ProcessSound, processSound)
        zox_sys_i(SoundData, soundData)
        zox_sys_i(SoundVolume, soundVolume)
        zox_sys_i(SoundFrequency, soundFrequency)
        zox_sys_o(TriggerSound, triggerSound)
        if (processSound->value != zox_sound_process_run) {
            continue;
        }
        if (!soundData->value) {
            zox_log_error("Failed processing, no sound data");
            continue;
        }
        const float frequency = soundFrequency->value;
        const float frequency_scale = frequency / default_frequency;
        float new_data[soundData->length];
        byte out_of_bounds = 0;
        for (int j = 0; j < soundData->length; j++) {
            if (out_of_bounds) {
                new_data[j] = 0.0f;
                continue;
            }
            const float source_index = j / frequency_scale;
            int index1 = (int) source_index;
            int index2 = index1 + 1;
            // Ensure indices are within bounds
            if (index2 >= soundData->length) {
                out_of_bounds = 1;
                new_data[j] = 0.0f;
                continue;
            }
            float time = source_index - index1;
            // Linear interpolation between samples
            new_data[j] = soundData->value[index1] * (1.0f - time) + soundData->value[index2] * time;
            new_data[j] *= soundVolume->value;
        }
        memcpy(soundData->value, new_data, soundData->length * sizeof(float));
        triggerSound->value = zox_sound_play_trigger;
        zox_log_sounds("  -> updated sound frequency to [%f]", frequency_scale);
    }
} zox_declare_system(SoundProcessSystem)