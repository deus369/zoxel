// todo: alter frequency over time during sound
void SoundGenerateSystem(ecs_iter_t *it) {
    if (nosounds) {
        return;
    }
    const float sound_bounds = 1.0f;
    zox_sys_begin()
    zox_sys_in(InstrumentType)
    zox_sys_in(SoundLength)
    zox_sys_in(SoundFrequency)
    zox_sys_in(SoundVolume)
    zox_sys_in(GenerateSound)
    zox_sys_in(SoundData)
    zox_sys_out(TriggerSound)
    for (int i = 0; i < it->count; i++) {
        zox_sys_i(SoundLength, soundLength)
        zox_sys_i(SoundFrequency, soundFrequency)
        zox_sys_i(InstrumentType, instrumentType)
        zox_sys_i(SoundVolume, soundVolume)
        zox_sys_i(GenerateSound, generateSound)
        zox_sys_i(SoundData, soundData)
        zox_sys_o(TriggerSound, triggerSound)
        if (generateSound->value != zox_sound_generate_run) {
            continue;
        }
        const float volume = soundVolume->value;
        const double sound_time_length = soundLength->value;
        const float frequency = soundFrequency->value;
        // const int data_length = (int) (sound_sample_rate * sound_time_length);
        const float noise = sound_noise * (rand() % 101) / 100.0f;
        // random.NextFloat(generateSound.noise.x, generateSound.noise.y);
        const byte instrument_type = instrumentType->value; // rand() % 3; // 2;
        const float attack = sound_attack_multiplier * sound_time_length; //  0.02f * sound_time_length;
        const float dampen = sound_dampen_multiplier * sound_time_length;

        // initialize_SoundData(soundData, data_length);
        float value = 0;
        for (int j = 0; j < soundData->length; j++) {
            const float time = (float) (j / sample_rate_f);
            if (instrument_type == instrument_piano) {
                value = piano_sound(time, frequency);
            } else if (instrument_type == instrument_piano_square) {
                value = piano_square_sound(time, frequency);
            } else if (instrument_type == instrument_unique) {
                value = unique_sound(time, frequency);
            } else if (instrument_type == instrument_organ) {
                value = organ_sound(time, frequency);
            } else if (instrument_type == instrument_edm) {
                value = edm_sound(time, frequency);
            } else if (instrument_type == instrument_guitar) {
                value = guitar_sound(time, frequency);
            } else if (instrument_type == instrument_flute) {
                value = flute_sound(time, frequency);
            } else if (instrument_type == instrument_violin) {
                value = violin_sound(time, frequency);
            } else if (instrument_type == instrument_saxophone) {
                value = saxophone_sound(time, frequency);
            } else if (instrument_type == instrument_trumpet) {
                value = trumpet_sound(time, frequency);
            } else {
                break;
            }
            if (noise) {
                value += noise * ((rand() / (float) RAND_MAX) * 2.0f - 1.0f);
            }
            value *= envelope(time, sound_time_length, attack, dampen);
            value *= volume;
            value = clampf(value, -sound_bounds, sound_bounds);
            soundData->value[j] = value;
        }
        triggerSound->value = zox_sound_play_trigger;
        zox_log_sounds("+ generated [%s] (%f)", zox_sys_e_name, volume)
    }
} zox_declare_system(SoundGenerateSystem)