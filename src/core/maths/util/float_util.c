float float_abs(float input) {
    if (input < 0) return -input;
    else return input;
}

float float_lerp(float a, float b, float t) {
    return (1 - t) * a + t * b;
}

float float_max(float a, float b) {
    if (a > b) return a;
    else return b;
}

float float_min(float a, float b) {
    if (a < b) return a;
    else return b;
}
