float modulate_0(float time_value, float frequency, float x)
{
    return 1 * sin(2.0f * M_PI * ((time_value) * frequency) + x);
}

float modulate_1(float time_value, float frequency, float x)
{	
    return 1.0f * sin(4.0f * M_PI * ((time_value) * frequency) + x);
}

float modulate_2(float time_value, float frequency, float x)
{	
    return 1.0f * sin(8.0f * M_PI * ((time_value) * frequency) + x);
}

float modulate_3(float time_value, float frequency, float x)
{	
    return 1.0f * sin(0.5f * M_PI * ((time_value) * frequency) + x);
}

float modulate_4(float time_value, float frequency, float x)
{	
    return 1.0f * sin(0.25f * M_PI * ((time_value) * frequency) + x);
}

float modulate_5(float time_value, float frequency, float x)
{	
    return 0.5f * sin(2.0f * M_PI * ((time_value) * frequency) + x);
}

float modulate_6(float time_value, float frequency, float x)
{	
    return 0.5f * sin(4.0f * M_PI * ((time_value) * frequency) + x);
}

float modulate_7(float time_value, float frequency, float x)
{	
    return 0.5f * sin(8.0f * M_PI * ((time_value) * frequency) + x);
}

float modulate_8(float time_value, float frequency, float x)
{	
    return 0.5f * sin(0.5f * M_PI * ((time_value) * frequency) + x);
}

float modulate_9(float time_value, float frequency, float x)
{	
    return 0.5f * sin(0.25f * M_PI * ((time_value) * frequency) + x);
}

void GenerateSoundSystem(ecs_iter_t *it)
{
    const float sound_bounds = 1.0f;
    const GenerateSound *generateSounds = ecs_field(it, GenerateSound, 2);
    SoundData *soundDatas = ecs_field(it, SoundData, 3);
    const SoundLength *soundLengths = ecs_field(it, SoundLength, 4);
    SoundDirty *soundDirtys = ecs_field(it, SoundDirty, 5);
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
        // printf("Generated sound.\n");
        soundDirty->value = 1;
        SoundData *soundData = &soundDatas[i];
        const SoundLength *soundLength = &soundLengths[i];
        // random.InitState((uint) seed.seed);
        double sound_time_length = soundLength->value; // soundData.sound_time_length;
        float frequency =  146.83f; // 440;    // random.NextFloat(generateSound.frequency.x, generateSound.frequency.y); // * sound_time_length;
        float noise = 0.1f + 0.1f * (rand() % 101) / 100.0f;     // random.NextFloat(generateSound.noise.x, generateSound.noise.y);
        int sampleRate = 44100; // (float) soundData.sampleRate;
        // var decay = generateSound.decay;
        float attack = 0.002f; // generateSound.attack;
        float volume = 1.0f; // sound.volume;
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
            if (noise != 0)
            {
                soundValue += noise * (rand() % 101) / 100.0f; // random.NextFloat(-noise, noise);
            }
            // Linear build-up, fast.
            if(i <= sampleRate * attack)
            {
                soundValue = soundValue * (i / (sampleRate * attack));
            }
            else // if (i >= 1 - sampleRate * decay)
            {
                //var dampen2 = Math.log((frequency*volume)/sampleRate);
                //var dampen3 = 1 + (0.01 * frequency);   
                float dampen = 0.0f;
                if (instrumentType == 0)
                {
                    dampen = pow(0.5f * log((frequency * volume) / sampleRate), 2.0f);
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
ECS_SYSTEM_DECLARE(GenerateSoundSystem);