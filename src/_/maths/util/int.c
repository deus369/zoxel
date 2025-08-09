static inline int abs_integer(int v) {
    return v < 0 ? -v : v;
}

static inline int int_min(int a, int b) {
    return a < b ? a : b;
}

static inline int int_max(int a, int b) {
    return a > b ? a : b;
}

static inline int int_absf(float v) {
    return v < 0 ? (int)-v : (int)v;
}

static inline int int_abs(int v) {
    return v < 0 ? (int)-v : (int)v;
}

static inline int int_floorf(float x) {
    // Rename to avoid clash with floor() macro or stdlib
    return (int)floorf(x);
}

static inline int int_clamp(int v, int lo, int hi) {
    return v < lo ? lo
    : v > hi ? hi
    : v;
}