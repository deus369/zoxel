/*int get_int3_hash(int3 input) {
    return input.x + 17 * input.y + 31 * input.z;
    // return 0;
}*/

// uses prime numbers:
// 2, 3, 5, 7, 11, 13, 17, 19, 23, 29, 31, 37, 41, 43, 47, 53, 59, 61, 67, 71, etc
// 73, 79, 83, 89, 97, 101, 103, 107, 109, 113, 127, 131, 137, 139, 149, 151, 157, 163, 167, 173
// uint32_t get_int3_hash(int3 input) {
//     /*uint32_t hash = 17;
//     hash = hash * 23 + ((uint32_t) input.x);
//     hash = hash * 23 + ((uint32_t) input.y);
//     hash = hash * 23 + ((uint32_t) input.z);*/
//     /*uint32_t hash = 61;
//     hash = hash * 71 + ((uint32_t) input.x);
//     hash = hash * 71 + ((uint32_t) input.y);
//     hash = hash * 71 + ((uint32_t) input.z);*/
//     uint32_t prime = 173;
//     uint32_t hash = 163;
//     // uint32_t hash = ;
//     /*hash = hash * prime + ((uint32_t) input.x);
//     hash = hash * prime + ((uint32_t) input.y);
//     hash = hash * prime + ((uint32_t) input.z);*/
//     hash = (hash ^ ((uint32_t) input.x)) * prime;
//     hash = (hash ^ ((uint32_t) input.y)) * prime;
//     hash = (hash ^ ((uint32_t) input.z)) * prime;
//     /*hash = (hash ^ input.x) * prime;
//     hash = (hash ^ input.y) * prime;
//     hash = (hash ^ input.z) * prime;*/
//     /*uint32_t x = (uint32_t)input.x;
//     uint32_t y = (uint32_t)input.y;
//     uint32_t z = (uint32_t)input.z;
//     // A good prime number for hashing
//     uint32_t prime = 4294967291;
//     // Initialize hash value to a random number
//     uint32_t hash = 2166136261;
//     // Mix input values with hash using a good hash function
//     hash = (hash ^ x) * prime;
//     hash = (hash ^ y) * prime;
//     hash = (hash ^ z) * prime;*/
//     return hash;
// }

// uint32_t get_int3_hash(int3 input) {
//     input.x = 1619 * input.x ^ 1013 * input.y ^ 1987 * input.z;
//     input.y = 4237 * input.x ^ 2777 * input.y ^ 1667 * input.z;
//     input.z = 5021 * input.x ^ 3617 * input.y ^ 2791 * input.z;
//     input.x = (input.x << 16) ^ (input.x >> 16);
//     input.y = (input.y << 16) ^ (input.y >> 16);
//     input.z = (input.z << 16) ^ (input.z >> 16);
//     return input.x ^ input.y ^ input.z;
// }

// #define HASH_PRIME1 31
// #define HASH_PRIME2 73856093

// uint32_t hash_int(int input) {
//     uint32_t hash = (uint32_t)(input * HASH_PRIME1);
//     hash = hash % HASH_PRIME2;
//     return hash;
// }
    /*const int m = 1540483477;
    uint32_t X0 = 0;
    uint32_t X1 = (hash_int(input.x) ^ X0) * m;
    uint32_t X2 = (hash_int(input.y) ^ X1) * m;
    uint32_t X3 = (hash_int(input.z) ^ X2) * m;*/

uint32_t hash_constant = 0x5bd1e995;

uint32_t get_int3_hash(int3 input) {
    uint32_t hash = hash_constant;
    hash = hash * 163 + ((uint32_t) input.x);
    hash = hash * 109 + ((uint32_t) input.y);
    hash = hash * 139 + ((uint32_t) input.z);
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
typedef struct name##_##pair name##_##pair;\
struct name##_##pair {\
    int key;\
    type value;\
    struct name##_##pair* next;\
};\
\
typedef struct {\
    int size;\
    name##_##pair **data;\
} name;\
\
int type##_##hash(int key, int size) {\
    return key % size;\
}\
\
name* create##_##name(int size) {\
    name* map = malloc(sizeof(name));\
    map->size = size;\
    map->data = calloc(size, sizeof(name##_##pair*));\
    return map;\
}\
\
void name##_##add(name* map, key_type key_raw, type value) {\
    int key = convert_to_hash(key_raw);\
    int index = type##_##hash(key, map->size);\
    name##_##pair* pair = malloc(sizeof(name##_##pair));\
    pair->key = key;\
    pair->value = value;\
    pair->next = map->data[index];\
    map->data[index] = pair;\
}\
\
type name##_##get(name* map, key_type key_raw) {\
    int key = convert_to_hash(key_raw);\
    int index = type##_##hash(key, map->size);\
    name##_##pair* pair = map->data[index];\
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
    name##_##pair* pair = map->data[index];\
    name##_##pair* prev_pair = NULL;\
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
        name##_##pair* pair = map->data[i];\
        while (pair != NULL) {\
            name##_##pair* next_pair = pair->next;\
            free(pair);\
            pair = next_pair;\
        }\
    }\
    free(map->data);\
    free(map);\
}

zoxel_hash_map(int3_hash_map, ecs_entity_t, 0, int3, get_int3_hash)