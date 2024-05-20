uint32_t hash_constant = 0x5bd1e995;

uint32_t get_int3_hash(int3 input) {
    uint32_t hash = hash_constant;
    hash = hash * 163 + ((uint32_t) input.x);
    hash = hash * 109 + ((uint32_t) input.y);
    hash = hash * 139 + ((uint32_t) input.z);
    return hash;
}

uint32_t get_int_hash(int input) {
    uint32_t hash = hash_constant;
    hash = hash * 163 + ((uint32_t) input);
    return hash;
}

uint32_t get_byte3_hash(byte3 input) {
    uint32_t hash = hash_constant;
    hash = hash * 163 + ((uint32_t) input.x);
    hash = hash * 109 + ((uint32_t) input.y);
    hash = hash * 139 + ((uint32_t) input.z);
    return hash;
}

zox_hash_map(int3_hash_map, ecs_entity_t, 0, int3, get_int3_hash)
zox_hash_map(int_hash_map, ecs_entity_t, 0, int, get_int_hash)
zox_hash_map(byte3_hash_map, ecs_entity_t, 0, byte3, get_byte3_hash)
