#define instrument_piano 0x00
#define instrument_piano_square 0x01
#define instrument_organ 0x02
#define instrument_edm 0x03
#define instrument_guitar 0x04
#define instrument_flute 0x05
#define instrument_violin 0x06
#define instrument_saxophone 0x07
#define instrument_trumpet 0x08
#define instrument_unique 0x09
#define instrument_end 10

float calculate_additive_comp(float time, float frequency, float lfo_frequency, float pi_offset, int iterations) {
    float additive_comp = 0.0f;
    for (int i = 1; i <= iterations; i++) {
        additive_comp += 0.2f * sin(2.0f * M_PI * frequency * i * time + pi_offset + 0.1f * sin(lfo_frequency * 0.2f * 2.0f * M_PI * time));
    }
    return additive_comp;
}

float high_pass_filter(float time, float cutoff_frequency) {
    // Biquad filter coefficients
    float b0, b1, a1, a2;
    // Sample rate
    // float sr = 44100;
    // Quality factor
    float Q = 1.0f; // 0.7f; 
    // Calculate filter coefficients
    float omega = 2 * M_PI * cutoff_frequency / sample_rate_f;
    float alpha = sin(omega) / (2 * Q);
    // a0 = 1 + alpha;
    b0 = (1 + cos(omega)) / 2;
    b1 = -(1 + cos(omega));
    // b2 = (1 + cos(omega)) / 2;
    a1 = -2 * cos(omega);
    a2 = 1 - alpha;
    // State variables
    static float x_1 = 0, x_2 = 0, y_1 = 0, y_2 = 0;
    x_1 = x_2;
    y_1 = y_2;
    x_2 = time;
    float output = b0 * x_2 + b1 * x_1 - a1 * y_1 - a2 * y_2;
    y_2 = output;
    return output;
}

float piano_sound(float time, float frequency) {
    return 0.75f * sin_wave_1(time, frequency,
        pow(sin_wave_0(time, frequency, 0.0f), 2.0f) + 
            (0.75f * sin_wave_0(time, frequency, 0.25f)) + 
            (0.5f * sin_wave_0(time, frequency, 0.5f)) );
}

float piano_square_sound(float time, float frequency) {
    return 0.94f * square_wave_1(time, frequency,
        pow(square_wave_0(time, frequency, 0.0f), 2.0f) + 
            (0.75f * square_wave_0(time, frequency, 0.25f)) + 
            (0.5f * square_wave_0(time, frequency, 0.5f)) );
}

float organ_sound(float time, float frequency) {
    return 0.94f * sin_wave_1(time, frequency,
        (sin_wave_0(time, frequency, 0.0f)) + 
        (0.5f * sin_wave_0(time, frequency, 0.25f)) + 
        (0.25f * sin_wave_0(time, frequency, 0.5f)));
}

float edm_sound(float time, float frequency) {
    return 0.6f * (sin_wave_0(time, frequency, 
        (sin_wave_9(time, frequency, 
            sin_wave_2(time, frequency, 
                pow(sin_wave_0(time, frequency, 0.0f), 3.0f) + 
                pow(sin_wave_0(time, frequency, 0.5f), 5.0f) + 
                pow(sin_wave_0(time, frequency, 1.0f), 7.0f)  )))) +
        sin_wave_8(time, frequency,
            sin_wave_1(time, frequency, 1.75f)));
}

float guitar_sound(float time, float frequency) {
    return 0.5f * (sin_wave_0(time, frequency,
        (sin_wave_1(time, frequency,
        sin_wave_2(time, frequency,
        pow(sin_wave_0(time, frequency, 0.0f), 2.0f) +
        pow(sin_wave_0(time, frequency, 0.5f), 3.0f) +
        pow(sin_wave_0(time, frequency, 1.0f), 4.0f) )))) +
        sin_wave_3(time, frequency,
            sin_wave_4(time, frequency, 1.75f)));
}

float flute_sound(float time, float frequency) {
    frequency *= 2.0f;
    float pi_offset = 0.0f;
    float lfo_frequency = 0.1f;    // .5
    // FM synthesis with a modulator frequency that varies over time
    float fm_comp = fm_synthesis_ext_0(time, frequency, frequency * (1.0f + 0.1f * sin(lfo_frequency * 2.0f * M_PI * time)), 0.1f);
    // Additive synthesis using multiple harmonic sine waves
    float additive_comp = 0.0f;
    for (int i = 1; i <= 12; i++) {
        additive_comp += 0.2f * sin(2.0f * M_PI * frequency * i * time + pi_offset + 0.1f * sin(lfo_frequency * 0.2f * 2.0f * M_PI * time));
    }
    // Noise component with a varying frequency
    float noise_comp = noise_wave_1(time) * (1.0f + 0.1f * sin(lfo_frequency * M_PI * time));
    // sawtooth component  with a varying frequency
    float sawtooth_comp = sawtooth_wave_12(time, frequency*0.5, pi_offset) * (1.0f + 0.1f * sin(lfo_frequency * 0.2f * M_PI * time));
    // Ring modulation with a slowly varying carrier frequency
    float ring_mod_comp = sin(frequency * 2.0f * M_PI * time + 0.1f * sin(lfo_frequency * 0.1f * 2.0f * M_PI * time));
    // Mix the various components together
    float final_comp = 1.0f / 3.0f * (fm_comp + additive_comp + noise_comp + sawtooth_comp + ring_mod_comp);
    // final_comp = high_pass_filter(final_comp, frequency * 2.1f);
    return final_comp;
    // Add a noise component to create a more breathy sound
    /*float breathy_comp = (sawtooth_wave_0(time, frequency / 2, pi_offset) + 
            triangle_wave_0(time, frequency / 4, pi_offset) +
            noise_wave_0(time)) / 4;
    // Add harmonics to create a more complex tone
    float tone_comp = (sin_wave_0(time, frequency, pi_offset) + 
            square_wave_0(time, frequency, pi_offset) + 
            sin_wave_1(time, frequency * 2, pi_offset) + 
            square_wave_1(time, frequency * 2, pi_offset) +
            fm_synthesis_0(time, frequency)) / 5;
    return breathy_comp + tone_comp;*/

    // return sawtooth_wave_0(time, frequency / 2, pi_offset);
    // return triangle_wave_0(time, frequency / 4, pi_offset);
}

float unique_sound(float time, float frequency) {
    float pi_offset = 0.0f;
    // float lfo_frequency = 1.0f; // frequency;
    float lfo_frequency = frequency;
    // FM synthesis with a modulator frequency that varies over time
    float fm_comp = fm_synthesis_ext_0(time, frequency, frequency * (1.0f + 0.1f * sin(lfo_frequency * 2.0f * M_PI * time)), 0.1f);
    // Additive synthesis using multiple harmonic sine waves
    float additive_comp = calculate_additive_comp(time, frequency, lfo_frequency, pi_offset, 12);
    // Noise component with a varying frequency
    float noise_comp = noise_wave_0(time) * (1.0f + 0.1f * sin(lfo_frequency * M_PI * time));
    // Ring modulation with a slowly varying carrier frequency
    float ring_mod_comp = sin(frequency * 2.0f * M_PI * time + 0.1f * sin(lfo_frequency * 0.1f * 2.0f * M_PI * time));
    // Amplitude modulation with a slowly varying depth
    float am_comp = sin(frequency * 2.0f * M_PI * time) * (1.0f + 0.1f * sin(lfo_frequency * 0.05f * 2.0f * M_PI * time));
    // Mix the various components together and return the result
    return 0.3f * (fm_comp + additive_comp + noise_comp + ring_mod_comp + am_comp);
}

float violin_sound(float time, float frequency) {
    // float frequency = 440.0f; // base frequency of an A note
    float pi_offset = 0.0f;
    float tremolo_frequency = 8.0f;
    float vibrato_frequency = 4.0f;
    return 0.75f * (0.5f * sin(frequency * M_PI * time + pi_offset)
        + 0.5f * sin_wave_3(time, frequency, pi_offset)
        + 0.25f * sin_wave_4(time, frequency, pi_offset)
        + 0.5f * pow(sin_wave_5(time, frequency, pi_offset), 2.0f)
        + 0.2f * sin_wave_6(time, frequency, pi_offset)
        + 0.1f * sin_wave_7(time, frequency, pi_offset)
        + 0.1f * sin_wave_8(time, frequency, pi_offset)
        + 0.1f * sin_wave_9(time, frequency, pi_offset)
        + 0.1f * sin_wave_0(time, tremolo_frequency, pi_offset)
        + 0.1f * sin_wave_1(time, vibrato_frequency, pi_offset));
}

float saxophone_sound(float time, float frequency) {
    return 0.5f * sin_wave_1(time, frequency,
        (sin_wave_2(time, frequency,
        sin_wave_3(time, frequency,
        pow(sin_wave_0(time, frequency, 0.0f), 3.0f) +
        pow(sin_wave_0(time, frequency, 0.25f), 5.0f) +
        pow(sin_wave_0(time, frequency, 0.5f), 7.0f) )))) +
        sin_wave_4(time, frequency, sin_wave_5(time, frequency, 2.0f));
}

float trumpet_sound(float time, float frequency) {
    return sin_wave_5(time, frequency,
        (sin_wave_6(time, frequency,
        sin_wave_7(time, frequency,
        pow(sin_wave_0(time, frequency, 0.0f), 3.0f) +
        pow(sin_wave_0(time, frequency, 0.25f), 5.0f) +
        pow(sin_wave_0(time, frequency, 0.5f), 7.0f) )))) +
        sin_wave_8(time, frequency, sin_wave_9(time, frequency, 2.0f));
}

    /*
    float tremolo_frequency = 8.0f;
    float vibrato_frequency = 4.0f;
    return 0.7f * (0.5f * sin(frequency * M_PI * time + pi_offset)
        + 0.5f * sin_wave_3(time, frequency, pi_offset)
        + 0.25f * sin_wave_4(time, frequency, pi_offset)
        + 0.5f * pow(sin_wave_5(time, frequency, pi_offset), 2.0f)
        + 0.2f * sin_wave_6(time, frequency, pi_offset)
        + 0.1f * sin_wave_7(time, frequency, pi_offset)
        + 0.1f * sin_wave_8(time, frequency, pi_offset)
        + 0.1f * sin_wave_9(time, frequency, pi_offset)
        + 0.1f * sin_wave_0(time, tremolo_frequency, pi_offset)
        + 0.1f * sin_wave_1(time, vibrato_frequency, pi_offset));*/

    // This is a simple flute sound generator that uses a combination of 
    // sine and square waves to create a realistic flute sound.
    // The parameters of the sine and square waves can be adjusted to 
    // change the timbre of the instrument.

    /*float pi_offset = 0.0f;
    return (sin_wave_0(time, frequency, pi_offset) + 
            square_wave_0(time, frequency, pi_offset) + 
            sin_wave_1(time, frequency, pi_offset) + 
            square_wave_1(time, frequency, pi_offset))/4;*/
            
    // This is an advanced flute sound generator that uses a combination of 
    // sine, square, sawtooth, triangle and FM synthesis waves to create a realistic flute sound.
    // The parameters of the waves can be adjusted to 
    // change the timbre of the instrument.
    
    /*float pi_offset = 0.0f;
    float breathy_comp = (sawtooth_wave_0(time, frequency / 2, 0)
        + triangle_wave_0(time, frequency / 4, 0)) / 4;
    float tone_comp = (sin_wave_0(time, frequency, pi_offset) + 
            square_wave_0(time, frequency, pi_offset) + 
            sin_wave_1(time, frequency, pi_offset) + 
            square_wave_1(time, frequency, pi_offset) +
            fm_synthesis_0(time, frequency)) / 5.0f;    // , frequency*1.01, 0.01
    return (breathy_comp + tone_comp); //  * envelope_function(time, frequency);
    */
    /*float pi_offset = 0.0f;
    float breathy_comp = (sawtooth_wave_0(time, frequency/2, pi_offset)
        + triangle_wave_0(time, frequency/4, pi_offset))/4;
    float tone_comp = (sin_wave_0(time, frequency, pi_offset) + 
            square_wave_0(time, frequency, pi_offset) + 
            sin_wave_1(time, frequency, pi_offset) + 
            square_wave_1(time, frequency, pi_offset) +
            fm_synthesis_0(time, frequency, frequency*1.01, 0.01))/5;
    return (breathy_comp + tone_comp);*/