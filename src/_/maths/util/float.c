static inline float float_abs(const float input) {
    return (input < 0) ? -input : input;
}

static inline float absf(const float input) {
    return (input < 0) ? -input : input;
}

static inline float float_sign(const float input) {
    if (input < 0) return -1;
    else if (input > 0) return 1;
    else return 0;
}

static inline float float_lerp(float a, float b, float t) {
    return (1 - t) * a + t * b;
}

static inline float float_max(float a, float b) {
    if (a > b) return a;
    else return b;
}

static inline float float_min(float a, float b) {
    if (a < b) return a;
    else return b;
}
