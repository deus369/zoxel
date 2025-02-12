float organ_sound(float time, float frequency) {
    return 0.94f * sin_wave_1(time, frequency,
                              (sin_wave_0(time, frequency, 0.0f)) +
                              (0.5f * sin_wave_0(time, frequency, 0.25f)) +
                              (0.25f * sin_wave_0(time, frequency, 0.5f)));
}