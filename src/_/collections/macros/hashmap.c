// default hash is uint
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
\
static inline void write_lock_##name(const name *component) {\
    if (hashmap_safety_locks) {\
        pthread_rwlock_wrlock((pthread_rwlock_t*) &component->lock);\
    }\
}\
\
static inline void read_lock_##name(const name *component) {\
    if (hashmap_safety_locks) {\
        pthread_rwlock_rdlock((pthread_rwlock_t*) &component->lock);\
    }\
}\
\
static inline void lock_unlock_##name(const name *component) {\
    if (hashmap_safety_locks) {\
        pthread_rwlock_unlock((pthread_rwlock_t*) &component->lock);\
    }\
}\
\
static inline void destroy_lock_##name(name *component) {\
    if (hashmap_safety_locks) {\
        pthread_rwlock_destroy(&component->lock);\
    }\
}\
\
static inline void create_lock_##name(name *component) {\
    if (hashmap_safety_locks) {\
        pthread_rwlock_init(&component->lock, NULL);\
    }\
}\
\
hash_type name##_hash(hash_type key, hash_type size) {\
    if (size == 0) {\
        return -1;\
    } else {\
        return key % size;\
    }\
}\
\
name* create_##name(hash_type size) {\
    if (size == 0) {\
        zox_log("! cannot have a zero hashmap [%s]", #name)\
        return NULL;\
    }\
    name* map = malloc(sizeof(name));\
    if (!map) {\
        zox_log_error("error creating hashmap [%s]\n", #name)\
        return NULL;\
    }\
    map->size = size;\
    /*calloc zeroes out data*/\
    map->data = calloc(size, sizeof(name##_pair*));\
    create_lock_##name(map);\
    return map;\
}\
\
void name##_add(name* map, key_type key_raw, type value) {\
    if (!map || !map->data || map->size == 0) {\
        return;\
    }\
    write_lock_##name(map);\
    hash_type key = convert_to_hash(key_raw);\
    hash_type index = name##_hash(key, map->size);\
    name##_pair* pair = malloc(sizeof(name##_pair));\
    pair->key = key;\
    pair->value = value;\
    pair->next = map->data[index];\
    map->data[index] = pair;\
    lock_unlock_##name(map);\
}\
\
type name##_get(name* map, key_type key_raw) {\
    if (!map || !map->data || map->size == 0) {\
        return type_zero;\
    }\
    read_lock_##name(map);\
    hash_type key = convert_to_hash(key_raw);\
    hash_type index = name##_hash(key, map->size);\
    name##_pair* pair = map->data[index];\
    uint checks = 0;\
    type value = type_zero;\
    while (pair != NULL && checks < max_safety_checks_hashmap) {\
        if (pair->key == key) {\
            value = pair->value;\
            break;\
        }\
        pair = pair->next;\
        checks++;\
    }\
    lock_unlock_##name(map);\
    return value;\
}\
\
byte name##_has(name* map, key_type key_raw) {\
    if (!map || !map->data || map->size == 0) {\
        return 1;\
    }\
    read_lock_##name(map);\
    hash_type key = convert_to_hash(key_raw);\
    hash_type index = name##_hash(key, map->size);\
    name##_pair* pair = map->data[index];\
    uint checks = 0;\
    while (pair != NULL && checks < max_safety_checks_hashmap) {\
        if (pair->key == key) {\
            lock_unlock_##name(map);\
            return 1;\
        }\
        pair = pair->next;\
        checks++;\
    }\
    lock_unlock_##name(map);\
    return 0;\
}\
\
void name##_remove(name* map, key_type key_raw) {\
    if (!map || !map->data || map->size == 0) {\
        return;\
    }\
    write_lock_##name(map);\
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
    lock_unlock_##name(map);\
}\
\
void name##_dispose(name* map) {\
    if (!map || map->size == 0 || !map->data) {\
        return;\
    }\
    write_lock_##name(map);\
    for (size_t i = 0; i < map->size; i++) {\
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
    lock_unlock_##name(map);\
    destroy_lock_##name(map);\
    free(map);\
}\
\
int count_##name(name* map) {\
    if (!map || !map->size) {\
        return 0;\
    }\
    read_lock_##name(map);\
    size_t count = 0;\
    for (size_t i = 0; i < map->size; i++) {\
        name##_pair* pair = map->data[i];\
        uint checks = 0;\
        while (pair != NULL && checks < max_safety_checks_hashmap) {\
            name##_pair* next_pair = pair->next;\
            count++;\
            pair = next_pair;\
            checks++;\
        }\
    }\
    lock_unlock_##name(map);\
    return count;\
}
