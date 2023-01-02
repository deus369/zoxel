// Use a macro to create our modulation functions for audio generation
#define modulate_function(index, amplitude, frequency_2)\
float modulate##_##index(float time_value, float frequency, float pi_offset)\
{\
    return amplitude * sin(frequency_2 * M_PI * time_value * frequency + pi_offset);\
}

modulate_function(0, 1.0f, 2.0f)
modulate_function(1, 1.0f, 4.0f)
modulate_function(2, 1.0f, 8.0f)
modulate_function(3, 1.0f, 0.5f)
modulate_function(4, 1.0f, 0.25f)
modulate_function(5, 0.5f, 2.0f)
modulate_function(6, 0.5f, 4.0f)
modulate_function(7, 0.5f, 8.0f)
modulate_function(8, 0.5f, 0.5f)
modulate_function(9, 0.5f, 0.25f)

void GenerateSoundSystem(ecs_iter_t *it)
{
    const int sampleRate = 44100; // (float) soundData.sampleRate;
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
        float frequency = soundFrequency->value; // 146.83f; // 440;    // random.NextFloat(generateSound.frequency.x, generateSound.frequency.y); // * sound_time_length;
        float noise = 0.1f + 0.1f * (rand() % 101) / 100.0f;     // random.NextFloat(generateSound.noise.x, generateSound.noise.y);
        //float attack = 0.002f;
        float attack = 0.02f;
        // float decay = 0.6f;
        float volume = 0.8f; // sound.volume;
        unsigned char instrumentType = rand() % 3; // 2;
        int total_sound_samples = (int) ( sampleRate * sound_time_length );
        initialize_memory_component(soundData, float, total_sound_samples);
        for (int i = 0; i < total_sound_samples; i++)
        {
            float time_value = ((float) i / sampleRate);
            float soundValue = 0.0f;
            // piano
            if (instrumentType == 0)
            {
                soundValue += modulate_1(time_value, frequency,
                    pow(modulate_0(time_value, frequency, 0.0f), 2.0f) + 
                        (0.75f * modulate_0(time_value, frequency, 0.25f)) + 
                        (0.5f * modulate_0(time_value, frequency, 0.5f)) );
            }
            // organ
            else if (instrumentType == 1)
            {
                soundValue += modulate_1(time_value, frequency,
                    (modulate_0(time_value, frequency, 0.0f)) + 
                    (0.5f * modulate_0(time_value, frequency, 0.25f)) + 
                    (0.25f * modulate_0(time_value, frequency, 0.5f)));
            }
            // edm
            else if (instrumentType == 2)
            {
                soundValue += modulate_0(time_value, frequency, 
                    (modulate_9(time_value, frequency, 
                        modulate_2(time_value, frequency, 
                            pow(modulate_0(time_value, frequency, 0.0f), 3.0f) + 
                            pow(modulate_0(time_value, frequency, 0.5f), 5.0f) + 
                            pow(modulate_0(time_value, frequency, 1.0f), 7.0f)  )))) +
                    modulate_8(time_value, frequency, modulate_1(time_value, frequency, 1.75f));
            }
            soundValue *= volume;
            if (noise != 0)
            {
                soundValue += - noise + 2.0f * noise * (rand() % 101) / 100.0f; // random.NextFloat(-noise, noise);
            }
            // Linear build-up, fast.
            // if (i <= sampleRate * attack)
            if (i <= total_sound_samples * attack)
            {
                // soundValue = soundValue * (i / (sampleRate * attack));
                soundValue *= (i / (total_sound_samples * attack));
            }
            // else if (i >= 1 - sampleRate * decay)
            else // if (i >= total_sound_samples - total_sound_samples * decay)
            { 
                float dampen = 0.0f;
                if (instrumentType == 0)
                {
                    // dampen = pow(0.5f * log((frequency * volume) / sampleRate), 2.0f);
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
                soundValue = soundValue * pow((1.0f - ((i - (sampleRate * attack)) / (sampleRate * (sound_time_length - attack)))), dampen);
            }
            soundValue = float_clamp(soundValue, -sound_bounds, sound_bounds);
            soundData->value[i] = soundValue;
        }
    }
}
zoxel_declare_system(GenerateSoundSystem)