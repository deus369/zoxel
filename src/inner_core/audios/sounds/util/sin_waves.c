// Use a macro to create our modulation functions for audio generation
#define sin_wave_function(index, amplitude, frequency_2)\
float sin_wave##_##index(float time_value, float frequency, float pi_offset)\
{\
    return amplitude * sin(frequency_2 * M_PI * time_value * frequency + pi_offset);\
}

sin_wave_function(0, 1.0f, 2.0f)
sin_wave_function(1, 1.0f, 4.0f)
sin_wave_function(2, 1.0f, 8.0f)
sin_wave_function(3, 1.0f, 0.5f)
sin_wave_function(4, 1.0f, 0.25f)
sin_wave_function(5, 0.5f, 2.0f)
sin_wave_function(6, 0.5f, 4.0f)
sin_wave_function(7, 0.5f, 8.0f)
sin_wave_function(8, 0.5f, 0.5f)
sin_wave_function(9, 0.5f, 0.25f)