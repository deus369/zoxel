// instrument_piano
// instrument_organ
// instrument_edm
// instrument_guitar
// instrument_flute
// instrument_violin
// instrument_piano_square
// instrument_saxophone
// instrument_trumpet
const unsigned char instrumentType = instrument_guitar;
const float attack_multiplier = 0.02f; // 0.04f
const float dampen_multiplier = 0.7f; // 0.92f

// sometimes envelop function has glitches?

void SoundGenerateSystem(ecs_iter_t *it)
{
    const float sound_bounds = 1.0f;
    const GenerateSound *generateSounds = ecs_field(it, GenerateSound, 2);
    const SoundLength *soundLengths = ecs_field(it, SoundLength, 3);
    const SoundFrequency *soundFrequencys = ecs_field(it, SoundFrequency, 4);
    SoundData *soundDatas = ecs_field(it, SoundData, 5);
    SoundDirty *soundDirtys = ecs_field(it, SoundDirty, 6);
    for (int i = 0; i < it->count; i++)
    {
        const GenerateSound *generateSound = &generateSounds[i];
        if (generateSound->value != 1)
        {
            continue;
        }
        SoundDirty *soundDirty = &soundDirtys[i];
        if (soundDirty->value != 0)
        {
            continue;
        }
        soundDirty->value = 1;
        SoundData *soundData = &soundDatas[i];
        const SoundLength *soundLength = &soundLengths[i];
        const SoundFrequency *soundFrequency = &soundFrequencys[i];
        // random.InitState((uint) seed.seed);
        double sound_time_length = soundLength->value; // soundData.sound_time_length;
        float frequency = soundFrequency->value;
        float noise = 0.06f * (rand() % 101) / 100.0f;     // random.NextFloat(generateSound.noise.x, generateSound.noise.y);
        // unsigned char instrumentType = 0; // rand() % 3; // 2;
        //float attack = 0.002f;
        float attack = attack_multiplier * sound_time_length; //  0.02f * sound_time_length;
        float dampen = dampen_multiplier * sound_time_length;
        float volume = 0.8f;
        int total_sound_samples = (int) ( sound_sample_rate * sound_time_length );
        initialize_memory_component(soundData, float, total_sound_samples);
        for (int i = 0; i < total_sound_samples; i++)
        {
            float time = (float) (i / sample_rate_f);
            float value = 0.0f;
            if (instrumentType == instrument_piano)
            {
                value = piano_sound(time, frequency);
            }
            else if (instrumentType == instrument_piano_square)
            {
                value = piano_square_sound(time, frequency);
            }
            else if (instrumentType == instrument_organ)
            {
                value = organ_sound(time, frequency);
            }
            else if (instrumentType == instrument_edm)
            {
                value = edm_sound(time, frequency);
            }
            else if (instrumentType == instrument_guitar)
            {
                value = guitar_sound(time, frequency);
            }
            else if (instrumentType == instrument_flute)
            {
                value = flute_sound(time, frequency);
            }
            else if (instrumentType == instrument_violin)
            {
                value = violin_sound(time, frequency);
            }
            else if (instrumentType == instrument_saxophone)
            {
                value = saxophone_sound(time, frequency);
            }
            else if (instrumentType ==  instrument_trumpet)
            {
                value = trumpet_sound(time, frequency);
            }
            if (noise != 0)
            {
                value += - noise + 2.0f * noise * (rand() % 101) / 100.0f; // random.NextFloat(-noise, noise);
            }
            value = apply_envelope(value, time, attack, dampen, sound_time_length);
            value *= volume;
            value = float_clamp(value, -sound_bounds, sound_bounds);
            soundData->value[i] = value;
        }
    }
}
zoxel_declare_system(SoundGenerateSystem)

            // Linear build-up, fast.
            // if (i <= sound_sample_rate * attack)
            // float dampen = pow(0.5f * log((frequency * volume) / total_sound_samples), 2.0f);

            /*if (i <= total_sound_samples * attack)
            {
                // value = value * (i / (sound_sample_rate * attack));
                value *= (i / (total_sound_samples * attack));
            }
            // else if (i >= 1 - sound_sample_rate * decay)
            else // if (i >= total_sound_samples - total_sound_samples * decay)
            { 
                float dampen = 0.0f;
                if (instrumentType == 0)
                {
                    // dampen = pow(0.5f * log((frequency * volume) / sound_sample_rate), 2.0f);
                    dampen = pow(0.5f * log((frequency * volume) / total_sound_samples), 2.0f);
                }
                else if (instrumentType == 1)
                {
                    dampen = 1 + (frequency * 0.01f);
                }
                else if (instrumentType == 2)
                {
                    dampen = 1;
                }
                //else
                {
                //    dampen = pow(0.5f * log((frequency * volume) / total_sound_samples), 2.0f);
                }
                value = value * pow((1.0f - ((i - (sound_sample_rate * attack)) / (sound_sample_rate * (sound_time_length - attack)))), dampen);
            }*/