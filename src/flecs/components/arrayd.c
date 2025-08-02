// Dynamic Arrays
#define zox_memory_component(T, type) \
typedef struct { \
    int length; \
    type *value; \
    SpinLock lock; \
} T; \
zox_custom_component(T) \
\
ECS_CTOR(T, ptr, { \
    ptr->length = 0; \
    ptr->value = NULL; \
    ptr->lock = SPINLOCK_INIT; \
}) \
\
ECS_DTOR(T, ptr, { \
    if (ptr->value) { \
        free(ptr->value); \
        ptr->value = NULL; \
        ptr->length = 0; \
    } \
})\
\
ECS_MOVE(T, dst, src, { \
    dst->value = src->value; \
    dst->length = src->length; \
    dst->lock = SPINLOCK_INIT; \
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
            dst->lock = SPINLOCK_INIT; \
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
void dispose_##T(T *ptr) {\
    if (ptr->value) {\
        free(ptr->value);\
        ptr->value = NULL;\
    }\
    ptr->length = 0;\
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
byte add_to_##T(T *ptr, const type data) { \
    spin_lock(&ptr->lock); \
    int new_length = ptr->length + 1; \
    type* new_value = ptr->value \
        ? realloc(ptr->value, new_length * sizeof(type)) \
        : malloc(new_length * sizeof(type)); \
    if (!new_value) { \
        zox_log_error("malloc failed in add_to_" #T); \
        spin_unlock(&ptr->lock); \
        return 0; \
    } \
    ptr->value = new_value; \
    ptr->value[ptr->length] = data; \
    ptr->length++; \
    spin_unlock(&ptr->lock); \
    return 1; \
}


#define zox_define_memory_component(T)\
    zox_define_component(T)\
    zox_define_hooks(T);
