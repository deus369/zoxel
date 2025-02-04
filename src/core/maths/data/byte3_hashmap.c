// using primes for unique hash
#define hash_constant_byte 37
#define hash_multiple_1 29 // 163
#define hash_multiple_2 31 // 109
#define hash_multiple_3 37 // 139

uint32_t get_byte3_hash(byte3 input) {
    uint32_t hash = hash_constant;
    hash = hash * 163 + ((uint32_t) input.x);
    hash = hash * 109 + ((uint32_t) input.y);
    hash = hash * 139 + ((uint32_t) input.z);
    return hash;
}