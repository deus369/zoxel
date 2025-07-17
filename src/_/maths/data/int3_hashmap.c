static inline uint get_int3_hash(int3 input) {
    uint hash = hash_constant;
    hash = hash * 163 + ((uint) input.x);
    hash = hash * 109 + ((uint) input.y);
    hash = hash * 139 + ((uint) input.z);
    return hash;
}
