int abs_integer(int value) {
    if (value < 0) {
        return -value;
    } else {
        return value;
    }
}

int integer_min(int a, int b) {
    if (a > b) {
        return b;
    } else {
        return a;
    }
}

float3 float3_from_int3(int3 input) {
    return (float3) { input.x, input.y, input.z };
}

int int_floor(float input) {
    return (int) floor(input);
}

int int_min(int a, int b) {
    if (a < b) {
        return a;
    } else {
        return b;
    }
}

int int_max(int a, int b) {
    if (a > b) {
        return a;
    } else {
        return b;
    }
}

int int_abs(float input) {
    if (input < 0) {
        return -input;
    } else {
        return input;
    }
}