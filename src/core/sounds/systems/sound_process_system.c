// todo: alter frequency over time during sound
void SoundProcessSystem(ecs_iter_t *it) {
    // return;
    zox_field_in(SoundFrequency, soundFrequencys, 1)
    zox_field_in(SoundData, soundDatas, 2)
    zox_field_out(ProcessSound, processSounds, 3)
    zox_field_out(TriggerSound, triggerSounds, 4)
    zox_field_out(SoundDirty, soundDirtys, 5)
    for (int i = 0; i < it->count; i++) {
        zox_field_o(ProcessSound, processSounds, processSound)
        if (!processSound->value) continue;
        // zox_log("process sound1\n")
        // if (triggerSound->value) continue;
        zox_field_i(SoundData, soundDatas, soundData)
        if (!soundData->value) zox_log("sound data issue\n")
        if (!soundData->value) continue;
        // zox_log("process sound2\n")
        zox_field_o(TriggerSound, triggerSounds, triggerSound)
        zox_field_o(SoundDirty, soundDirtys, soundDirty)
        zox_field_i(SoundFrequency, soundFrequencys, soundFrequency)
        const float frequency = soundFrequency->value;
        const float default_frequency = 440;
        const float frequency_scale = frequency / default_frequency;
        float new_data[soundData->length];
        for (int j = 0; j < soundData->length; j++) {
            const float source_index = j / frequency_scale;
            int index1 = (int)source_index;
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
        processSound->value = 0;
        triggerSound->value = 1;
        soundDirty->value = 1;
        // zox_log(" frequency_scale [%f]\n", frequency_scale)
    }
} zox_declare_system(SoundProcessSystem)
