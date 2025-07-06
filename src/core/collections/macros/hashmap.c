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
    pthread_rwlock_t lock;\
} name;\
\
hash_type name##_hash(hash_type key, hash_type size) {\
    if (size == 0) return -1;\
    return key % size;\
}\
\
name* create_##name(hash_type size) {\
    if (size == 0) {\
        zox_log("! cannot have a zero hashmap [%s]\n", #name)\
        return NULL;\
    }\
    name* map = malloc(sizeof(name));\
    map->size = size;\
    /*calloc zeroes out data*/\
    map->data = calloc(size, sizeof(name##_pair*));\
    pthread_rwlock_init(&map->lock, NULL);\
    return map;\
}\
\
void name##_add(name* map, key_type key_raw, type value) {\
    if (!map || !map->data || map->size == 0) {\
        return;\
    }\
    pthread_rwlock_wrlock(&map->lock);\
    hash_type key = convert_to_hash(key_raw);\
    hash_type index = name##_hash(key, map->size);\
    name##_pair* pair = malloc(sizeof(name##_pair));\
    pair->key = key;\
    pair->value = value;\
    pair->next = map->data[index];\
    map->data[index] = pair;\
    pthread_rwlock_unlock(&map->lock);\
}\
\
type name##_get(name* map, key_type key_raw) {\
    if (!map || !map->data || map->size == 0) {\
        return type_zero;\
    }\
    pthread_rwlock_rdlock(&map->lock);\
    hash_type key = convert_to_hash(key_raw);\
    hash_type index = name##_hash(key, map->size);\
    name##_pair* pair = map->data[index];\
    int checks = 0;\
    type value = type_zero;\
    while (pair != NULL && checks < max_safety_checks_hashmap) {\
        if (pair->key == key) {\
            value = pair->value;\
            break;\
        }\
        pair = pair->next;\
        checks++;\
    }\
    pthread_rwlock_unlock(&map->lock);\
    return value;\
}\
\
byte name##_has(name* map, key_type key_raw) {\
    if (!map || !map->data || map->size == 0) {\
        return 1;\
    }\
    pthread_rwlock_rdlock(&map->lock);\
    hash_type key = convert_to_hash(key_raw);\
    hash_type index = name##_hash(key, map->size);\
    name##_pair* pair = map->data[index];\
    int checks = 0;\
    while (pair != NULL && checks < max_safety_checks_hashmap) {\
        if (pair->key == key) {\
            pthread_rwlock_unlock(&map->lock);\
            return 1;\
        }\
        pair = pair->next;\
        checks++;\
    }\
    pthread_rwlock_unlock(&map->lock);\
    return 0;\
}\
\
void name##_remove(name* map, key_type key_raw) {\
    if (!map || !map->data || map->size == 0) {\
        return;\
    }\
    pthread_rwlock_wrlock(&map->lock);\
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
            break;\
        }\
        prev_pair = pair;\
        pair = pair->next;\
        checks++;\
    }\
    pthread_rwlock_unlock(&map->lock);\
}\
\
void name##_dispose(name* map) {\
    if (!map || map->size == 0 || !map->data) {\
        return;\
    }\
    pthread_rwlock_wrlock(&map->lock);\
    for (int i = 0; i < map->size; i++) {\
        name##_pair* pair = map->data[i];\
        uint checks = 0;\
        while (pair != NULL && checks < max_safety_checks_hashmap) {\
            name##_pair* next_pair = pair->next;\
            free(pair);\
            pair = next_pair;\
            checks++;\
        }\
    }\
    free(map->data);\
    pthread_rwlock_unlock(&map->lock);\
    pthread_rwlock_destroy(&map->lock);\
    free(map);\
}\
\
int count_##name(name* map) {\
    if (!map || map->size == 0) {\
        return 0;\
    }\
    pthread_rwlock_rdlock(&map->lock);\
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
    pthread_rwlock_unlock(&map->lock);\
    return count;\
}
