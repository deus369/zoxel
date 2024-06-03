uint32_t get_byte3_hash(byte3 input) {
    uint32_t hash = hash_constant;
    hash = hash * 163 + ((uint32_t) input.x);
    hash = hash * 109 + ((uint32_t) input.y);
    hash = hash * 139 + ((uint32_t) input.z);
    return hash;
}

zox_hashmap(byte3_hashmap, ecs_entity_t, 0, byte3, get_byte3_hash)
