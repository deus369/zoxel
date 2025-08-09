// Dynamic Arrays
#define zoxc_arrayd(T, type) \
typedef struct { \
    int length; \
    type *value; \
    SpinLock lock; \
} T; \
zoxc_custom(T); \
\
ECS_CTOR(T, ptr, { \
    /*zox_log_error("   - ECS_CTOR %s", #T);*/ \
    ptr->length = 0; \
    ptr->value = NULL; \
    ptr->lock = SPINLOCK_INIT; \
}) \
\
void dispose_##T(T *ptr) {\
    if (ptr->value) {\
        zee(ptr->value);\
        ptr->value = NULL;\
    }\
    ptr->length = 0;\
}\
\
void dispose_##T##_const(const T *ptr) {\
    if (ptr->value) {\
        zee(ptr->value);\
    }\
}\
\
ECS_DTOR(T, ptr, { \
    /*zox_log_error("   - DTOR %s %i", #T, ptr->length);*/ \
    if (ptr->value) { \
        zee(ptr->value); \
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
    /*zox_log("   - ECS_MOVE %i %s", dst->length, #T);*/ \
}) \
\
ECS_COPY(T, dst, src, { \
    /*zox_log("   - ECS_COPY %i %s", src->length, #T);*/ \
    if (src->value && src->length > 0) { \
        dst->value = zalloc(src->length * sizeof(type)); \
        if (!dst->value) { \
            zox_log_error("zalloc failed in ECS_COPY [%s]", #T); \
            dst->value = NULL; \
            dst->length = 0; \
            return; \
        } \
        memcpy(dst->value, src->value, src->length * sizeof(type)); \
        dst->length = src->length; \
        dst->lock = SPINLOCK_INIT; \
    } else { \
        dst->value = NULL; \
        dst->length = 0; \
    } \
}) \
\
void clone_##T(T* dst, const T* src) {\
    if (!src->value) {\
        dispose_##T(dst);\
    } else {\
        int memory_length = src->length * sizeof(type);\
        type *new_memory = zalloc(memory_length);\
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
        type *new_memory = zalloc(length * sizeof(type));\
        if (!new_memory) {\
            zox_log_error("zalloc failure " #T);\
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
        ? rezalloc(ptr->value, new_length * sizeof(type)) \
        : zalloc(new_length * sizeof(type)); \
    if (!new_value) { \
        zox_log_error("zalloc failed in add_to_" #T); \
        spin_unlock(&ptr->lock); \
        return 0; \
    } \
    ptr->value = new_value; \
    ptr->value[ptr->length] = data; \
    ptr->length++; \
    spin_unlock(&ptr->lock); \
    return 1; \
} \
\
byte remove_at_##T(T *ptr, int index) {\
    spin_lock(&ptr->lock); \
    if (!ptr->value || index < 0 || index >= ptr->length) {\
        spin_unlock(&ptr->lock); \
        return 0;\
    }\
    for (int i = index; i < ptr->length - 1; i++) {\
        ptr->value[i] = ptr->value[i + 1];\
    }\
    ptr->length--;\
    if (!ptr->length) {\
        zee(ptr->value);\
        ptr->value = NULL;\
    } else {\
        ptr->value = rezalloc(ptr->value, ptr->length * sizeof(type));\
    }\
    spin_unlock(&ptr->lock); \
    return 1;\
}


#define zox_define_memory_component(T)\
    zox_define_component(T)\
    zox_define_hooks(T);

// equals function required here
#define zoxc_arrayd_removes(T, type) \
byte remove_from_##T(T* ptr, const type data) { \
    spin_lock(&ptr->lock); \
    int index = -1; \
    for (int i = 0; i < ptr->length; i++) { \
        if (ptr->value[i] == data) { \
            index = i; \
            break;\
        }\
    }\
    spin_unlock(&ptr->lock); \
    if (index == -1) { \
        return 0; \
    } \
    return remove_at_##T(ptr, index);\
}

#define resize_memory_component(T, ptr, type, new_length) {\
    if (ptr->length != new_length) {\
        if (new_length == 0) {\
            dispose_##T(ptr);\
        } else if (ptr->value) {\
            type* new_memory = rezalloc(ptr->value, new_length * sizeof(type));\
            if (!new_memory) {\
                zox_log_error("Failure with realloc");\
            } else {\
                ptr->value = new_memory;\
                ptr->length = new_length;\
            }\
        } else {\
            initialize_##T(ptr, new_length);\
        }\
    }\
}
