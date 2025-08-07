const byte powers_of_two_byte[] = {
    1,
    2,
    4,
    8,
    16,
    32,
    64,
    128
};

const float powers_of_two[] = {
    1,
    2,
    4,
    8,
    16,
    32,
    64,
    128,
    256,
    512,
    1024,
    2048
};

static inline int next_power_of_two(int n) {
    if (n <= 0) {
        return 1;
    }
    n--;
    n |= n >> 1;
    n |= n >> 2;
    n |= n >> 4;
    n |= n >> 8;
    n |= n >> 16;
    return n + 1;
}

static inline int next_power_of_two_root_safe(int n) {
    if (n <= 0) {
        return 1;
    }
    int root = 1;
    while (root * root < n) {
        root *= 2;
    }
    return root;
}

// Only works if `n` is under ~2^30
static inline int next_power_of_two_root(int n) {
    if (n <= 0) return 1;
    int log2val = (int)ceil(log2(n) / 2.0);
    return 1 << log2val;
}