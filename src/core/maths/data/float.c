static inline float float_clamp(const float v, const float lo, const float hi) {
    return v < lo ? lo
    : v > hi ? hi
    : v;
}