const float attack_multiplier = 0.02f; // 0.04f
const float dampen_multiplier = 0.7f; // 0.92f

void SoundGenerateSystem(ecs_iter_t *it) {
    #ifdef zoxel_time_sound_generate_system
        begin_timing()
    #endif
    // const float sound_bounds = 1.0f;
    const float volume = 1.0f; // 0.8f;
    const GenerateSound *generateSounds = ecs_field(it, GenerateSound, 2);
    const SoundLength *soundLengths = ecs_field(it, SoundLength, 3);
    const SoundFrequency *soundFrequencys = ecs_field(it, SoundFrequency, 4);
    const InstrumentType *instrumentTypes = ecs_field(it, InstrumentType, 5);
    SoundData *soundDatas = ecs_field(it, SoundData, 6);
    SoundDirty *soundDirtys = ecs_field(it, SoundDirty, 7);
    for (int i = 0; i < it->count; i++) {
        const GenerateSound *generateSound = &generateSounds[i];
        if (generateSound->value != 1) {
            continue;
        }
        SoundDirty *soundDirty = &soundDirtys[i];
        if (soundDirty->value != 0) {
            continue;
        }
        soundDirty->value = 1;
        SoundData *soundData = &soundDatas[i];
        const SoundLength *soundLength = &soundLengths[i];
        const SoundFrequency *soundFrequency = &soundFrequencys[i];
        const InstrumentType *instrumentType = &instrumentTypes[i];
        #ifdef zoxel_log_sound_generation
            printf("Sound played. Instrument [%i]. Frequency [%f]. Length [%f].\n",
                instrumentType->value, soundFrequency->value, soundLength->value);
        #endif
        // random.InitState((uint) seed.seed);
        double sound_time_length = soundLength->value; // soundData.sound_time_length;
        float frequency = soundFrequency->value;
        float noise = 0.04f * (rand() % 101) / 100.0f;     // random.NextFloat(generateSound.noise.x, generateSound.noise.y);
        unsigned char instrument_type = instrumentType->value; // rand() % 3; // 2;
        //float attack = 0.002f;
        float attack = attack_multiplier * sound_time_length; //  0.02f * sound_time_length;
        float dampen = dampen_multiplier * sound_time_length;
        int total_sound_samples = (int) ( sound_sample_rate * sound_time_length );
        initialize_memory_component(soundData, float, total_sound_samples);
        for (int i = 0; i < total_sound_samples; i++) {
            float time = (float) (i / sample_rate_f);
            float value = 0.0f;
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
            } else if (instrument_type ==  instrument_trumpet) {
                value = trumpet_sound(time, frequency);
            } else {
                break;
                continue;
            }
            if (noise != 0) {
                value += noise * ((rand() / (float) RAND_MAX) * 2.0f - 1.0f);
            }
            value *= envelope(time, sound_time_length, attack, dampen);
            value *= volume;
            // value = float_clamp(value, -sound_bounds, sound_bounds);
            soundData->value[i] = value;
        }
        #ifdef zoxel_time_sound_generate_system
            did_do_timing()
        #endif
    }
    #ifdef zoxel_time_sound_generate_system
        end_timing("SoundGenerateSystem")
    #endif
}
zoxel_declare_system(SoundGenerateSystem)

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