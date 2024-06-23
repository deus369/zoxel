void SoundGenerateSystem(ecs_iter_t *it) {
    zox_field_in(SoundLength, soundLengths, 5)
    zox_field_in(SoundFrequency, soundFrequencys, 6)
    zox_field_in(SoundVolume, soundVolumes, 7)
    zox_field_in(InstrumentType, instrumentTypes, 8)
    zox_field_out(GenerateSound, generateSounds, 2)
    zox_field_out(SoundData, soundDatas, 3)
    zox_field_out(SoundDirty, soundDirtys, 4)
    for (int i = 0; i < it->count; i++) {
        zox_field_o(GenerateSound, generateSounds, generateSound)
        if (!generateSound->value) continue;
        zox_field_o(SoundDirty, soundDirtys, soundDirty)
        if (soundDirty->value) continue;
        zox_field_o(SoundData, soundDatas, soundData)
        zox_field_i(SoundLength, soundLengths, soundLength)
        zox_field_i(SoundFrequency, soundFrequencys, soundFrequency)
        zox_field_i(InstrumentType, instrumentTypes, instrumentType)
        zox_field_i(SoundVolume, soundVolumes, soundVolume)
        const float volume = soundVolume->value;
        const double sound_time_length = soundLength->value; // soundData.sound_time_length;
        const float frequency = soundFrequency->value;
        const float noise = sound_noise * (rand() % 101) / 100.0f;
        // random.NextFloat(generateSound.noise.x, generateSound.noise.y);
        const unsigned char instrument_type = instrumentType->value; // rand() % 3; // 2;
        const float attack = sound_attack_multiplier * sound_time_length; //  0.02f * sound_time_length;
        const float dampen = sound_dampen_multiplier * sound_time_length;
        const int total_sound_samples = (int) (sound_sample_rate * sound_time_length);
        resize_memory_component(SoundData, soundData, float, total_sound_samples)
        for (int j = 0; j < total_sound_samples; j++) {
            const float time = (float) (j / sample_rate_f);
            float value = 0.0f;
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

            const float sound_bounds = 1.0f;
            value = float_clamp(value, -sound_bounds, sound_bounds);

            soundData->value[j] = value;
        }
        generateSound->value = 0;
        soundDirty->value = 1;
#ifdef zoxel_log_sound_generation
        zox_log(" > sound generated: instrument [%i] frequency [%f] length [%f]\n", instrumentType->value, soundFrequency->value, soundLength->value)
#endif
    }
} zox_declare_system(SoundGenerateSystem)
