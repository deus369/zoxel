// using primes for unique hash
#define hash_constant_byte 37
#define hash_multiple_1 29 // 163
#define hash_multiple_2 31 // 109
#define hash_multiple_3 37 // 139

// remember: max number is 65,535
/*uint16_t get_byte3_hash(byte3 input) {
    uint16_t hash = hash_constant_byte; // hash_constant
    hash = hash * hash_multiple_1 + ((uint16_t) input.x);
    hash = hash * hash_multiple_2 + ((uint16_t) input.y);
    hash = hash * hash_multiple_3 + ((uint16_t) input.z);
    return hash;
}*/

uint32_t get_byte3_hash(byte3 input) {
    uint32_t hash = hash_constant;
    hash = hash * 163 + ((uint32_t) input.x);
    hash = hash * 109 + ((uint32_t) input.y);
    hash = hash * 139 + ((uint32_t) input.z);
    return hash;
}

zox_hashmap(byte3_hashmap, ecs_entity_t, 0, byte3, uint32_t, get_byte3_hash)

/*
 *
    uint32_t hash = hash_constant;

    hash ^= ((uint32_t)input.x) * 0x45d9f3b;
    hash ^= ((uint32_t)input.y) * 0x119de1f3;
    hash ^= ((uint32_t)input.z) * 0x344bc55;

    hash ^= (hash >> 16);
    hash *= 0x85ebca6b;
    hash ^= (hash >> 13);
    hash *= 0xc2b2ae35;
    hash ^= (hash >> 16);
*/


/*
 * uint8_t get_byte3_hash(byte3 input) {
    uint8_t hash = hash_constant;
    hash = hash * 163 + ((uint8_t) input.x);
    hash = hash * 109 + ((uint8_t) input.y);
    hash = hash * 139 + ((uint8_t) input.z);
    return hash;
}
*/
