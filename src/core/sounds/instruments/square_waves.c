#define square_wave_function(index, amplitude, frequency_2)\
float square_wave##_##index(float time, float frequency, float pi_offset)\
{\
    float value = amplitude * sin(frequency_2 * M_PI * time * frequency + pi_offset);\
    if (value > 0) return amplitude;\
    else return -amplitude;\
}

square_wave_function(0, 1.0f, 2.0f)
square_wave_function(1, 1.0f, 4.0f)
square_wave_function(2, 1.0f, 8.0f)
square_wave_function(3, 1.0f, 0.5f)
square_wave_function(4, 1.0f, 0.25f)
square_wave_function(5, 0.5f, 2.0f)
square_wave_function(6, 0.5f, 4.0f)
square_wave_function(7, 0.5f, 8.0f)
square_wave_function(8, 0.5f, 0.5f)
square_wave_function(9, 0.5f, 0.25f)