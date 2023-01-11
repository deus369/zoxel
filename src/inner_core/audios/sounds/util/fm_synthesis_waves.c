#define fm_synthesis_function(index, amplitude, pi_offset)\
float fm_synthesis_##index(float time, float frequency)\
{\
    float carrier_frequency = frequency;\
    float modulator_frequency = frequency * 1.01;\
    float modulation = 0.01;\
    return amplitude * sin(carrier_frequency * 2.0f * M_PI * time +\
        modulation * sin(modulator_frequency * 2.0f * M_PI * time + pi_offset));\
}

fm_synthesis_function(0, 1.0f, 2.0f)
fm_synthesis_function(1, 1.0f, 4.0f)
fm_synthesis_function(2, 1.0f, 8.0f)
fm_synthesis_function(3, 1.0f, 0.5f)
fm_synthesis_function(4, 1.0f, 0.25f)

#define fm_synthesis_function_ext(index, amplitude, pi_offset)\
float fm_synthesis_ext_##index(float time, float carrier_frequency, float modulator_frequency, float modulation)\
{\
    return amplitude * sin(carrier_frequency * 2.0f * M_PI * time +\
        modulation * sin(modulator_frequency * 2.0f * M_PI * time + pi_offset));\
}

fm_synthesis_function_ext(0, 1.0f, 2.0f)
fm_synthesis_function_ext(1, 1.0f, 4.0f)
fm_synthesis_function_ext(2, 1.0f, 8.0f)
fm_synthesis_function_ext(3, 1.0f, 0.5f)
fm_synthesis_function_ext(4, 1.0f, 0.25f)