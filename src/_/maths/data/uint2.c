#define uint2_zero (uint2) { 0, 0 }

static inline byte uint2_equals(const uint2 a, const uint2 b) {
    return a.x == b.x && a.y == b.y;
}