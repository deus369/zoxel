static inline uint32_t get_int_hash(int input) {
    return hash_constant * 163 + ((uint32_t) input);
}