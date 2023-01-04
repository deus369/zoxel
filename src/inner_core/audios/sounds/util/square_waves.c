#define square_wave(index, amplitude, frequency_2)\
float square_wave##_##index(float time, float frequency, float pi_offset)\
{\
    float value = amplitude * sin(frequency_2 * M_PI * time * frequency + pi_offset);\
    if (value > 0) return amplitude;\
    else return -amplitude;\
}

square_wave(0, 1.0f, 2.0f)
square_wave(1, 1.0f, 4.0f)
square_wave(2, 1.0f, 8.0f)
square_wave(3, 1.0f, 0.5f)
square_wave(4, 1.0f, 0.25f)
square_wave(5, 0.5f, 2.0f)
square_wave(6, 0.5f, 4.0f)
square_wave(7, 0.5f, 8.0f)
square_wave(8, 0.5f, 0.5f)
square_wave(9, 0.5f, 0.25f)