uint32_t get_int_hash(int input) {
    uint32_t hash = hash_constant;
    hash = hash * 163 + ((uint32_t) input);
    return hash;
}