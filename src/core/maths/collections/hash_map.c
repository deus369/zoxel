/*int get_int3_hash(int3 input) {
    return input.x + 17 * input.y + 31 * input.z;
    // return 0;
}*/


uint32_t get_int3_hash(int3 input) {
    uint32_t hash = 17;
    hash = hash * 23 + (uint32_t) input.x;
    hash = hash * 23 + (uint32_t) input.y;
    hash = hash * 23 + (uint32_t) input.z;
    return hash;
}

/*uint32_t murmur3_32(const void* key, size_t len, uint32_t seed) {
    const uint8_t* data = (const uint8_t*)key;
    const int nblocks = len / 4;

    uint32_t h1 = seed;

    const uint32_t c1 = 0xcc9e2d51;
    const uint32_t c2 = 0x1b873593;

    // body
    const uint32_t* blocks = (const uint32_t*)(data + nblocks*4);

    for (int i = -nblocks; i; i++) {
        uint32_t k1 = blocks[i];

        k1 *= c1;
        k1 = (k1 << 15) | (k1 >> (32 - 15));
        k1 *= c2;

        h1 ^= k1;
        h1 = (h1 << 13) | (h1 >> (32 - 13));
        h1 = h1*5 + 0xe6546b64;
    }

    // tail
    const uint8_t* tail = (const uint8_t*)(data + nblocks*4);

    uint32_t k1 = 0;

    switch (len & 3) {
        case 3:
            k1 ^= tail[2] << 16;
        case 2:
            k1 ^= tail[1] << 8;
        case 1:
            k1 ^= tail[0];
            k1 *= c1;
            k1 = (k1 << 15) | (k1 >> (32 - 15));
            k1 *= c2;
            h1 ^= k1;
    }

    // finalize
    h1 ^= len;

    h1 ^= h1 >> 16;
    h1 *= 0x85ebca6b;
    h1 ^= h1 >> 13;
    h1 *= 0xc2b2ae35;
    h1 ^= h1 >> 16;

    return h1;
}

// Hash function for int3 objects using MurmurHash3
int get_int3_hash(int3 pos) {
    uint32_t hash = murmur3_32(&pos, sizeof(int3), 0);
    return (int)hash;
}*/

// zoxel_log(" - index [%i]\n", index);

#define zoxel_hash_map(name, type, type_zero, key_type, convert_to_hash)\
typedef struct type##_##hash_pair type##_##hash_pair;\
struct type##_##hash_pair\
{\
    int key;\
    type value;\
    struct type##_##hash_pair* next;\
};\
\
typedef struct {\
    int size;\
    type##_##hash_pair **data;\
} name;\
\
int type##_##hash(int key, int size) {\
    return key % size;\
}\
\
name* create##_##name(int size) {\
    name* map = malloc(sizeof(name));\
    map->size = size;\
    map->data = calloc(size, sizeof(type##_##hash_pair*));\
    return map;\
}\
\
void name##_##add(name* map, key_type key_raw, type value) {\
    int key = convert_to_hash(key_raw);\
    int index = type##_##hash(key, map->size);\
    type##_##hash_pair* pair = malloc(sizeof(type##_##hash_pair));\
    pair->key = key;\
    pair->value = value;\
    pair->next = map->data[index];\
    map->data[index] = pair;\
}\
\
type name##_##get(name* map, key_type key_raw) {\
    int key = convert_to_hash(key_raw);\
    int index = type##_##hash(key, map->size);\
    type##_##hash_pair* pair = map->data[index];\
    while (pair != NULL) {\
        if (pair->key == key) {\
            return pair->value;\
        }\
        pair = pair->next;\
    }\
    return type_zero;\
}\
\
void name##_##remove(name* map, key_type key_raw) {\
    int key = convert_to_hash(key_raw);\
    int index = type##_##hash(key, map->size);\
    type##_##hash_pair* pair = map->data[index];\
    type##_##hash_pair* prev_pair = NULL;\
    while (pair != NULL) {\
        if (pair->key == key) {\
            if (prev_pair == NULL) {\
                map->data[index] = pair->next;\
            } else {\
                prev_pair->next = pair->next;\
            }\
            free(pair);\
            return;\
        }\
        prev_pair = pair;\
        pair = pair->next;\
    }\
}\
\
void name##_##dispose(name* map) {\
    for (int i = 0; i < map->size; i++) {\
        type##_##hash_pair* pair = map->data[i];\
        while (pair != NULL) {\
            type##_##hash_pair* next_pair = pair->next;\
            free(pair);\
            pair = next_pair;\
        }\
    }\
    free(map->data);\
    free(map);\
}

zoxel_hash_map(int3_hash_map, ecs_entity_t, 0, int3, get_int3_hash)