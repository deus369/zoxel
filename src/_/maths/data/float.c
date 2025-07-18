static inline float clampf(const float v, const float lo, const float hi) {
    return v < lo ? lo
    : v > hi ? hi
    : v;
}