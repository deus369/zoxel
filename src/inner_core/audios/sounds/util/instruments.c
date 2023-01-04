#define instrument_piano 0x00
#define instrument_piano_square 0x01
#define instrument_organ 0x02
#define instrument_edm 0x03
#define instrument_guitar 0x04
#define instrument_flute 0x05
#define instrument_violin 0x06
#define instrument_saxophone 0x07
#define instrument_trumpet 0x08

float piano_sound(float time, float frequency)
{
    return modulate_1(time, frequency,
        pow(modulate_0(time, frequency, 0.0f), 2.0f) + 
            (0.75f * modulate_0(time, frequency, 0.25f)) + 
            (0.5f * modulate_0(time, frequency, 0.5f)) );
}

float piano_square_sound(float time, float frequency)
{
    return square_wave_1(time, frequency,
        pow(square_wave_0(time, frequency, 0.0f), 2.0f) + 
            (0.75f * square_wave_0(time, frequency, 0.25f)) + 
            (0.5f * square_wave_0(time, frequency, 0.5f)) );
}

float organ_sound(float time, float frequency)
{
    return modulate_1(time, frequency,
        (modulate_0(time, frequency, 0.0f)) + 
        (0.5f * modulate_0(time, frequency, 0.25f)) + 
        (0.25f * modulate_0(time, frequency, 0.5f)));
}

float edm_sound(float time, float frequency)
{
    return modulate_0(time, frequency, 
        (modulate_9(time, frequency, 
            modulate_2(time, frequency, 
                pow(modulate_0(time, frequency, 0.0f), 3.0f) + 
                pow(modulate_0(time, frequency, 0.5f), 5.0f) + 
                pow(modulate_0(time, frequency, 1.0f), 7.0f)  )))) +
        modulate_8(time, frequency,
            modulate_1(time, frequency, 1.75f));
}

float violin_sound(float time, float frequency)
{
    // float frequency = 440.0f; // base frequency of an A note
    float pi_offset = 0.0f;
    float amplitude = 0.5f;
    float tremolo_frequency = 8.0f;
    float vibrato_frequency = 4.0f;
    return (amplitude * sin(frequency * M_PI * time + pi_offset)
        + 0.5f * modulate_3(time, frequency, pi_offset)
        + 0.25f * modulate_4(time, frequency, pi_offset)
        + 0.5f * pow(modulate_5(time, frequency, pi_offset), 2.0f)
        + 0.2f * modulate_6(time, frequency, pi_offset)
        + 0.1f * modulate_7(time, frequency, pi_offset)
        + 0.1f * modulate_8(time, frequency, pi_offset)
        + 0.1f * modulate_9(time, frequency, pi_offset)
        + 0.1f * modulate_0(time, tremolo_frequency, pi_offset)
        + 0.1f * modulate_1(time, vibrato_frequency, pi_offset));
}

float flute_sound(float time, float frequency)
{
    float pi_offset = 0.0f;
    float amplitude = 0.5f;
    float volume = 1.0f;
    float tremolo_frequency = 8.0f;
    float vibrato_frequency = 4.0f;
    return volume * (amplitude * sin(frequency * M_PI * time + pi_offset)
        + 0.5f * modulate_3(time, frequency, pi_offset)
        + 0.25f * modulate_4(time, frequency, pi_offset)
        + 0.5f * pow(modulate_5(time, frequency, pi_offset), 2.0f)
        + 0.2f * modulate_6(time, frequency, pi_offset)
        + 0.1f * modulate_7(time, frequency, pi_offset)
        + 0.1f * modulate_8(time, frequency, pi_offset)
        + 0.1f * modulate_9(time, frequency, pi_offset)
        + 0.1f * modulate_0(time, tremolo_frequency, pi_offset)
        + 0.1f * modulate_1(time, vibrato_frequency, pi_offset));
}

float guitar_sound(float time, float frequency)
{
    return modulate_0(time, frequency,
        (modulate_1(time, frequency,
        modulate_2(time, frequency,
        pow(modulate_0(time, frequency, 0.0f), 2.0f) +
        pow(modulate_0(time, frequency, 0.5f), 3.0f) +
        pow(modulate_0(time, frequency, 1.0f), 4.0f) )))) +
        modulate_3(time, frequency,
            modulate_4(time, frequency, 1.75f));
}

float trumpet_sound(float time, float frequency)
{
    return modulate_5(time, frequency,
        (modulate_6(time, frequency,
        modulate_7(time, frequency,
        pow(modulate_0(time, frequency, 0.0f), 3.0f) +
        pow(modulate_0(time, frequency, 0.25f), 5.0f) +
        pow(modulate_0(time, frequency, 0.5f), 7.0f) )))) +
        modulate_8(time, frequency, modulate_9(time, frequency, 2.0f));
}

float saxophone_sound(float time, float frequency)
{
    return modulate_1(time, frequency,
        (modulate_2(time, frequency,
        modulate_3(time, frequency,
        pow(modulate_0(time, frequency, 0.0f), 3.0f) +
        pow(modulate_0(time, frequency, 0.25f), 5.0f) +
        pow(modulate_0(time, frequency, 0.5f), 7.0f) )))) +
        modulate_4(time, frequency, modulate_5(time, frequency, 2.0f));
}