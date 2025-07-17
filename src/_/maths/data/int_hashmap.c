static inline uint get_int_hash(int input) {
    return hash_constant * 163 + ((uint) input);
}