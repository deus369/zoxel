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