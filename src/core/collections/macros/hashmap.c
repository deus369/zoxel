const uint max_safety_checks_hashmap = 1024;
// default hash is uint32_t
#define zox_hashmap(name, type, type_zero, key_type, hash_type, convert_to_hash)\
\
typedef struct name##_pair name##_pair;\
\
struct name##_pair {\
    hash_type key;\
    type value;\
    struct name##_pair* next;\
};\
\
typedef struct {\
    hash_type size;\
    name##_pair **data;\
} name;\
\
hash_type name##_hash(hash_type key, hash_type size) {\
    if (size == 0) return -1;\
    return key % size;\
}\
\
name* create_##name(hash_type size) {\
    name* map = malloc(sizeof(name));\
    map->size = size;\
    /*calloc zeroes out data*/\
    map->data = calloc(size, sizeof(name##_pair*));\
    /*const int byte_length = size * sizeof(name##_##pair*);*/\
    /*map->data = malloc(byte_length);*/\
    /*memset(map->data, 0, byte_length);*/\
    return map;\
}\
\
void name##_add(name* map, key_type key_raw, type value) {\
    if (!map || !map->data) return;\
    hash_type key = convert_to_hash(key_raw);\
    /*zox_log("key [%i]\n", key)*/\
    hash_type index = name##_hash(key, map->size);\
    name##_pair* pair = malloc(sizeof(name##_pair));\
    pair->key = key;\
    pair->value = value;\
    pair->next = map->data[index];\
    map->data[index] = pair;\
}\
\
type name##_get(name* map, key_type key_raw) {\
    if (!map || !map->data) return type_zero;\
    hash_type key = convert_to_hash(key_raw);\
    hash_type index = name##_hash(key, map->size);\
    name##_pair* pair = map->data[index];\
    int checks = 0;\
    while (pair != NULL && checks < max_safety_checks_hashmap) {\
        if (pair->key == key) return pair->value;\
        pair = pair->next;\
        checks++;\
    }\
    return type_zero;\
}\
\
unsigned char name##_has(name* map, key_type key_raw) {\
    if (!map || !map->data) return 1;\
    hash_type key = convert_to_hash(key_raw);\
    hash_type index = name##_hash(key, map->size);\
    name##_pair* pair = map->data[index];\
    int checks = 0;\
    while (pair != NULL && checks < max_safety_checks_hashmap) {\
        if (pair->key == key) return 1;\
        pair = pair->next;\
        checks++;\
    }\
    return 0;\
}\
\
void name##_remove(name* map, key_type key_raw) {\
    if (!map || !map->data) return;\
    hash_type key = convert_to_hash(key_raw);\
    hash_type index = name##_hash(key, map->size);\
    name##_pair* pair = map->data[index];\
    name##_pair* prev_pair = NULL;\
    uint checks = 0;\
    while (pair != NULL && checks < max_safety_checks_hashmap) {\
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
        checks++;\
    }\
}\
\
void name##_dispose(name* map) {\
    if (!map) return;\
    if (!map->data) {\
        /*free(map);*/\
        return;\
    }\
    for (int i = 0; i < map->size; i++) {\
        name##_pair* pair = map->data[i];\
        uint checks = 0;\
        while (pair != NULL && checks < max_safety_checks_hashmap) {\
            name##_##pair* next_pair = pair->next;\
            free(pair);\
            pair = next_pair;\
            checks++;\
        }\
    }\
    /* randomly this became a memory leak??*/\
    /*free(map->data);*/\
    /*free(map);*/\
}\
\
int count_##name(name* map) {\
    if (!map) return 0;\
    int count = 0;\
    for (int i = 0; i < map->size; i++) {\
        name##_pair* pair = map->data[i];\
        uint checks = 0;\
        while (pair != NULL && checks < max_safety_checks_hashmap) {\
            name##_pair* next_pair = pair->next;\
            count++;\
            pair = next_pair;\
            checks++;\
        }\
    }\
    return count;\
}
