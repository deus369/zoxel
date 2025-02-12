

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