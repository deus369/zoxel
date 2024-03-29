// instrument_piano
// instrument_organ
// instrument_edm
// instrument_guitar
// instrument_flute
// instrument_violin
// instrument_piano_square
// instrument_saxophone
// instrument_trumpet
// const unsigned char instrumentType = instrument_piano;
// sometimes envelop function has glitches?

void SoundGenerateSystem(ecs_iter_t *it) {
#ifdef zoxel_time_sound_generate_system
    begin_timing()
#endif
    GenerateSound *generateSounds = ecs_field(it, GenerateSound, 2);
    SoundData *soundDatas = ecs_field(it, SoundData, 3);
    SoundDirty *soundDirtys = ecs_field(it, SoundDirty, 4);
    const SoundLength *soundLengths = ecs_field(it, SoundLength, 5);
    const SoundFrequency *soundFrequencys = ecs_field(it, SoundFrequency, 6);
    const SoundVolume *soundVolumes = ecs_field(it, SoundVolume, 7);
    const InstrumentType *instrumentTypes = ecs_field(it, InstrumentType, 8);
    for (int i = 0; i < it->count; i++) {
        GenerateSound *generateSound = &generateSounds[i];
        if (!generateSound->value) continue;
        SoundDirty *soundDirty = &soundDirtys[i];
        if (soundDirty->value) continue;
        SoundData *soundData = &soundDatas[i];
        const SoundLength *soundLength = &soundLengths[i];
        const SoundFrequency *soundFrequency = &soundFrequencys[i];
        const InstrumentType *instrumentType = &instrumentTypes[i];
        const SoundVolume *soundVolume = &soundVolumes[i];
        float volume = soundVolume->value;
        double sound_time_length = soundLength->value; // soundData.sound_time_length;
        float frequency = soundFrequency->value;
        float noise = sound_noise * (rand() % 101) / 100.0f;     // random.NextFloat(generateSound.noise.x, generateSound.noise.y);
        unsigned char instrument_type = instrumentType->value; // rand() % 3; // 2;
        float attack = sound_attack_multiplier * sound_time_length; //  0.02f * sound_time_length;
        float dampen = sound_dampen_multiplier * sound_time_length;
        int total_sound_samples = (int) (sound_sample_rate * sound_time_length);
        generateSound->value = 0;
        resize_memory_component(SoundData, soundData, float, total_sound_samples)
        /*if (soundData->value == NULL) {
            zox_log("   ! entity [%lu] failed to alloc sound data [%i]\n", it->entities[i], total_sound_samples)
            continue;
        }*/
        for (int j = 0; j < total_sound_samples; j++) {
            float time = (float) (j / sample_rate_f);
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
            // value = float_clamp(value, -sound_bounds, sound_bounds);
            soundData->value[j] = value;
        }
        soundDirty->value = 1;
#ifdef zoxel_log_sound_generation
        zox_log(" > sound generated: instrument [%i] frequency [%f] length [%f]\n", instrumentType->value, soundFrequency->value, soundLength->value)
#endif
#ifdef zoxel_time_sound_generate_system
        did_do_timing()
#endif
    }
#ifdef zoxel_time_sound_generate_system
    end_timing("SoundGenerateSystem")
#endif
} zox_declare_system(SoundGenerateSystem)
