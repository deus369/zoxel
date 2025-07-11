// todo: alter frequency over time during sound
void SoundGenerateSystem(ecs_iter_t *it) {
    const float sound_bounds = 1.0f;
    zox_sys_world()
    zox_field_in(InstrumentType, instrumentTypes, 1)
    zox_field_in(SoundLength, soundLengths, 2)
    zox_field_in(SoundFrequency, soundFrequencys, 3)
    zox_field_in(SoundVolume, soundVolumes, 4)
    zox_field_out(GenerateSound, generateSounds, 5)
    zox_field_out(SoundData, soundDatas, 6)
    zox_field_out(SoundDirty, soundDirtys, 7)
    for (int i = 0; i < it->count; i++) {
        zox_field_i(SoundLength, soundLengths, soundLength)
        zox_field_i(SoundFrequency, soundFrequencys, soundFrequency)
        zox_field_i(InstrumentType, instrumentTypes, instrumentType)
        zox_field_i(SoundVolume, soundVolumes, soundVolume)
        zox_field_o(GenerateSound, generateSounds, generateSound)
        zox_field_o(SoundDirty, soundDirtys, soundDirty)
        zox_field_o(SoundData, soundDatas, soundData)
        if (!generateSound->value || soundDirty->value) {
            continue;
        }
        const float volume = soundVolume->value;
        const double sound_time_length = soundLength->value;
        const float frequency = soundFrequency->value;
        const float noise = sound_noise * (rand() % 101) / 100.0f;
        // random.NextFloat(generateSound.noise.x, generateSound.noise.y);
        const byte instrument_type = instrumentType->value; // rand() % 3; // 2;
        const float attack = sound_attack_multiplier * sound_time_length; //  0.02f * sound_time_length;
        const float dampen = sound_dampen_multiplier * sound_time_length;
        const int total_sound_samples = (int) (sound_sample_rate * sound_time_length);
        if (generateSound->value == 1) {
            resize_memory_component(SoundData, soundData, float, total_sound_samples)
        }
        const int split = (int) (ceil(total_sound_samples / sound_generation_splitter)) + 1;
        const int start_j = (int) ((generateSound->value - 1) * split);
        int end_j = start_j + split;
        if (end_j > total_sound_samples) end_j = total_sound_samples;
        float value = 0.0f;
        for (int j = start_j; j < end_j; j++) {
            const float time = (float) (j / sample_rate_f);
            if (instrument_type == instrument_piano) value = piano_sound(time, frequency);
            else if (instrument_type == instrument_piano_square) value = piano_square_sound(time, frequency);
            else if (instrument_type == instrument_unique) value = unique_sound(time, frequency);
            else if (instrument_type == instrument_organ) value = organ_sound(time, frequency);
            else if (instrument_type == instrument_edm) value = edm_sound(time, frequency);
            else if (instrument_type == instrument_guitar) value = guitar_sound(time, frequency);
            else if (instrument_type == instrument_flute) value = flute_sound(time, frequency);
            else if (instrument_type == instrument_violin) value = violin_sound(time, frequency);
            else if (instrument_type == instrument_saxophone) value = saxophone_sound(time, frequency);
            else if (instrument_type ==  instrument_trumpet) value = trumpet_sound(time, frequency);
            else break;
            if (noise) value += noise * ((rand() / (float) RAND_MAX) * 2.0f - 1.0f);
            value *= envelope(time, sound_time_length, attack, dampen);
            value *= volume;
            value = float_clamp(value, -sound_bounds, sound_bounds);
            soundData->value[j] = value;
        }
        generateSound->value++;
        if (generateSound->value > sound_generation_splitter) {
            generateSound->value = 0;
            soundDirty->value = 1;
            zox_field_e()
            zox_log_sounds(" > [%f] sound [%s] generated: instrument [%i] frequency [%f] length [%f]", zox_current_time, zox_get_name(e), instrumentType->value, soundFrequency->value, soundLength->value)
        }
    }
} zox_declare_system(SoundGenerateSystem)