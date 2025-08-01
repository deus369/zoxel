/*
#define sawtooth_wave_function(index, amplitude, frequency_2)\
float sawtooth_wave##_##index(float time, float frequency, float pi_offset)\
{\
    float t = time * frequency * frequency_2;\
    return amplitude * (2.0f * (t - floor(t + pi_offset)));\
}
*/

#define sawtooth_wave_function(index, amplitude, frequency_2)\
float sawtooth_wave##_##index(float time, float frequency, float pi_offset)\
{\
    float t = time * frequency * frequency_2 + pi_offset;\
    return amplitude * (2.0f * (t - floor(t)) - 1.0f);\
}


// return amplitude * (time_value * frequency - floor(time_value * frequency));
// return amplitude * (zox_fmod((frequency * time_value) + offset, 1.0f) * 2.0f - 1.0f);

sawtooth_wave_function(0, 1.0f, 2.0f)
sawtooth_wave_function(1, 1.0f, 4.0f)
sawtooth_wave_function(2, 1.0f, 8.0f)
sawtooth_wave_function(3, 1.0f, 0.5f)
sawtooth_wave_function(4, 1.0f, 0.25f)
sawtooth_wave_function(5, 0.5f, 2.0f)
sawtooth_wave_function(6, 0.5f, 4.0f)
sawtooth_wave_function(7, 0.5f, 8.0f)
sawtooth_wave_function(8, 0.5f, 0.5f)
sawtooth_wave_function(9, 0.5f, 0.25f)

sawtooth_wave_function(12, 0.05f, 2.0f)