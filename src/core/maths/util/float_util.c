float float_abs(float input) {
    if (input < 0) return -input;
    else return input;
}

float float_lerp(float a, float b, float t) {
    return (1 - t) * a + t * b;
}