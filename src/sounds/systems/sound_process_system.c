// todo: alter frequency over time during sound
void SoundProcessSystem(ecs_iter_t *it) {
    const float default_frequency = 220; // 440;
    zox_sys_begin()
    zox_sys_in(SoundFrequency)
    zox_sys_in(SoundData)
    zox_sys_in(ProcessSound)
    zox_sys_out(TriggerSound)
    for (int i = 0; i < it->count; i++) {
        zox_sys_i(SoundData, soundData)
        zox_sys_i(SoundFrequency, soundFrequency)
        zox_sys_i(ProcessSound, processSound)
        zox_sys_o(TriggerSound, triggerSound)
        if (processSound->value != zox_sound_process_run || !soundData->value) {
            continue;
        }
        const float frequency = soundFrequency->value;
        const float frequency_scale = frequency / default_frequency;
        float new_data[soundData->length];
        for (int j = 0; j < soundData->length; j++) {
            const float source_index = j / frequency_scale;
            int index1 = (int) source_index;
            int index2 = index1 + 1;
            float t = source_index - index1;
            // Ensure indices are within bounds
            if (index2 >= soundData->length) {
                new_data[j] = 0.0f; // Fill with silence if out of bounds
            } else {
                // Linear interpolation between samples
                new_data[j] = soundData->value[index1] * (1.0f - t) + soundData->value[index2] * t;
            }
        }
        memcpy(soundData->value, new_data, soundData->length * sizeof(float));
        triggerSound->value = zox_sound_play_trigger;
        zox_log_sounds("  -> updated sound frequency to [%f]", frequency_scale)
    }
} zox_declare_system(SoundProcessSystem)