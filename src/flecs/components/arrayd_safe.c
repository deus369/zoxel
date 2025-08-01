// Dynamic Arrays
// assumes non zero

#define zox_memory_component(T, type)\
\
int T##_memorys_allocated = 0;\
typedef struct {\
    int length;\
    type *value;\
    pthread_rwlock_t lock;\
} T;\
zox_custom_component(T)\
\
static inline void write_lock_##T(const T *ptr) {\
    if (memory_component_safety_locks) {\
        pthread_rwlock_wrlock((pthread_rwlock_t*) &ptr->lock);\
    }\
}\
\
static inline void read_lock_##T(const T *ptr) {\
    if (memory_component_safety_locks) {\
        pthread_rwlock_rdlock((pthread_rwlock_t*) &ptr->lock);\
    }\
}\
\
static inline void lock_unlock_##T(const T *ptr) {\
    if (memory_component_safety_locks) {\
        pthread_rwlock_unlock((pthread_rwlock_t*) &ptr->lock);\
    }\
}\
\
static inline void create_lock_##T(T *ptr) {\
    if (memory_component_safety_locks) {\
        pthread_rwlock_init(&ptr->lock, NULL);\
    }\
}\
\
static inline void destroy_lock_##T(T *ptr) {\
    if (memory_component_safety_locks) {\
        pthread_rwlock_destroy(&ptr->lock);\
    }\
}\
\
ECS_DTOR(T, ptr, { \
    if (ptr->value) { \
        free(ptr->value); \
        ptr->value = NULL; \
        ptr->length = 0; \
    } \
    destroy_lock_##T(ptr); \
})\
\
ECS_MOVE(T, dst, src, { \
    dst->value = src->value; \
    dst->length = src->length; \
    src->value = NULL; \
    src->length = 0; \
}) \
\
ECS_COPY(T, dst, src, { \
    if (src->value && src->length > 0) { \
        dst->value = malloc(src->length * sizeof(type)); \
        if (dst->value) { \
            memcpy(dst->value, src->value, src->length * sizeof(type)); \
            dst->length = src->length; \
        } else { \
            dst->value = NULL; \
            dst->length = 0; \
        } \
    } else { \
        dst->value = NULL; \
        dst->length = 0; \
    } \
}) \
\
ECS_CTOR(T, ptr, { \
    ptr->length = 0; \
    ptr->value = NULL; \
    create_lock_##T(ptr); \
}) \
\
void dispose_##T(T *ptr) {\
    if (!ptr->value) {\
        return;\
    }\
    write_lock_##T(ptr);\
    free(ptr->value);\
    ptr->value = NULL;\
    ptr->length = 0;\
    lock_unlock_##T(ptr);\
    destroy_lock_##T(ptr);\
    /*zox_log(" [%s] disposing of entity with memory component\n", #name)*/\
}\
\
void clone_##T(T* dst, const T* src) {\
    if (!src->value) {\
        dispose_##T(dst);\
    } else {\
        int memory_length = src->length * sizeof(type);\
        type *new_memory = malloc(memory_length);\
        if (!new_memory) {\
            zox_log_error("Failed allocating memory in clone_" #T);\
            return;\
        }\
        if (dst->value) {\
            dispose_##T(dst);\
        }\
        memcpy(new_memory, src->value, memory_length);\
        dst->value = new_memory;\
        dst->length = src->length;\
    }\
}\
\
void initialize_##T(T* ptr, int length) {\
    if (length > 0) {\
        type *new_memory = malloc(length * sizeof(type));\
        if (!new_memory) {\
            zox_log_error("malloc failure " #T);\
            ptr->value = NULL;\
            ptr->length = 0;\
        } else {\
            ptr->value = new_memory;\
            ptr->length = length;\
        }\
    } else {\
        ptr->value = NULL;\
        ptr->length = 0;\
    }\
} \
\
byte add_to_##T(T *ptr, const type data) {\
    write_lock_##T(ptr);\
    if (ptr->value) {\
        int new_length = ptr->length + 1;\
        int memory_length = (new_length) * sizeof(type);\
        type *new_memory = realloc(ptr->value, memory_length);\
        if (!new_memory) {\
            zox_log_error("failed realloc memory in add_to_" #T "");\
            lock_unlock_##T(ptr);\
            return 0;\
        }\
        ptr->value = new_memory;\
        ptr->length++;\
    } else {\
        initialize_##T(ptr, 1);\
    }\
    if (!ptr->value) {\
        ptr->length = 0;\
        lock_unlock_##T(ptr);\
        return 0;\
    }\
    ptr->value[ptr->length - 1] = data;\
    lock_unlock_##T(ptr);\
    return 1;\
}


#define zox_define_memory_component(T)\
    zox_define_component(T)\
    zox_define_hooks(T);
