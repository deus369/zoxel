uint32_t get_int3_hash(int3 input) {
    uint32_t hash = hash_constant;
    hash = hash * 163 + ((uint32_t) input.x);
    hash = hash * 109 + ((uint32_t) input.y);
    hash = hash * 139 + ((uint32_t) input.z);
    return hash;
}

zox_hashmap(int3_hashmap, ecs_entity_t, 0, int3, uint32_t, get_int3_hash)
