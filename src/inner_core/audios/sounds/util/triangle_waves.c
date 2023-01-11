#define triangle_wave_function(index, amplitude, frequency_2)\
float triangle_wave##_##index(float time, float frequency, float pi_offset)\
{\
    float t = time * frequency + pi_offset;\
    return amplitude * (2.0f * fabs(t - 2.0f * floor(t / 2.0f) - 1.0f) - 1.0f);\
}

triangle_wave_function(0, 1.0f, 2.0f)
triangle_wave_function(1, 1.0f, 4.0f)
triangle_wave_function(2, 1.0f, 8.0f)
triangle_wave_function(3, 1.0f, 0.5f)
triangle_wave_function(4, 1.0f, 0.25f)
triangle_wave_function(5, 0.5f, 2.0f)
triangle_wave_function(6, 0.5f, 4.0f)
triangle_wave_function(7, 0.5f, 8.0f)
triangle_wave_function(8, 0.5f, 0.5f)
triangle_wave_function(9, 0.5f, 0.25f)