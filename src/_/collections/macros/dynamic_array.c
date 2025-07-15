#define initial_dynamic_array_size 16

#define zoxel_dynamic_array(data_type)\
typedef struct {\
    data_type *data;\
    size_t capacity;\
    size_t size;\
} data_type##_##array_d;\
\
data_type##_##array_d* create##_##data_type##_##array_d(int initial_dynamic_array_size_) {\
    data_type##_##array_d* dynamic_array = malloc(sizeof(data_type##_##array_d));\
    dynamic_array->data = malloc(initial_dynamic_array_size_ * sizeof(data_type));\
    dynamic_array->capacity = initial_dynamic_array_size_;\
    dynamic_array->size = 0;\
    return dynamic_array;\
}\
\
void dispose##_##data_type##_##array_d(data_type##_##array_d* dynamic_array) {\
    free(dynamic_array->data);\
    free(dynamic_array);\
}\
\
void add_to##_##data_type##_##array_d(data_type##_##array_d* dynamic_array, data_type array_entry) {\
    if (dynamic_array->size == dynamic_array->capacity) {\
        dynamic_array->capacity *= 2;\
        dynamic_array->data = realloc(dynamic_array->data, dynamic_array->capacity * sizeof(data_type));\
    }\
    dynamic_array->data[dynamic_array->size++] = array_entry;\
}\
\
void expand_capacity##_##data_type##_##array_d(data_type##_##array_d* dynamic_array, int add_count) {\
    size_t required_capacity = dynamic_array->size + add_count;\
    if (required_capacity > dynamic_array->capacity) {\
        dynamic_array->capacity *= 2;\
        dynamic_array->data = realloc(dynamic_array->data, dynamic_array->capacity * sizeof(data_type));\
    }\
}\
\
void add_block_to##_##data_type##_##array_d(data_type##_##array_d* dynamic_array, const data_type block[], byte length) {\
    size_t required_capacity = dynamic_array->size + length; \
    if (required_capacity > dynamic_array->capacity) { \
        dynamic_array->capacity *= 2;\
        dynamic_array->data = realloc(dynamic_array->data, dynamic_array->capacity * sizeof(data_type));\
    }\
    memcpy(dynamic_array->data + dynamic_array->size, block, length * sizeof(data_type)); \
    dynamic_array->size += length; \
}\
\
void add_block_to##_##data_type##_##array_d2(data_type##_##array_d* dynamic_array, const data_type block[], byte length) {\
    size_t required_capacity = dynamic_array->size + length;\
    if (required_capacity > dynamic_array->capacity) {\
        dynamic_array->capacity *= 2;\
        dynamic_array->data = realloc(dynamic_array->data, dynamic_array->capacity * sizeof(data_type));\
    }\
    memcpy(dynamic_array->data + dynamic_array->size, block, length * sizeof(data_type));\
    for (byte i = 0; i < length; i++) dynamic_array->data[dynamic_array->size + i] = block[i];\
    dynamic_array->size += length; \
}\
\
data_type* finalize_##data_type##_##array_d(data_type##_##array_d* dynamic_array) {\
    if (!dynamic_array->size) {\
        dispose##_##data_type##_##array_d(dynamic_array);\
        return NULL;\
    } else if (dynamic_array->size == dynamic_array->capacity) {\
        data_type* data = dynamic_array->data;\
        free(dynamic_array);\
        return data;\
    } else {\
        data_type* data = realloc(dynamic_array->data, dynamic_array->size * sizeof(data_type));\
        free(dynamic_array);\
        return data;\
    }\
}

#define create_is_in_array_d(data_type)\
byte is_in##_##data_type##_##array_d(data_type##_##array_d* dynamic_array, const data_type value) {\
    for (int i = 0; i < dynamic_array->size; i++) if (dynamic_array->data[i] == value) return 1;\
    return 0;\
}

/*

*/
/*
#define finalize_dynamic_array(name, data_type, data_type##_##array_d* dynamic_array)\
data_type* return##_##name = finalize##_##data_type##_##array_d(dynamic_array);\
if (return##_##name) {\
    total_memorys_allocated++;\
    name##_##memorys_allocated++;\
}\
return return##_##name;
*/


/*
data_type* finalize##_##data_type##_##array_d2(data_type##_##array_d* dynamic_array) {\
    if (dynamic_array->size == 0) {\
        dispose##_##data_type##_##array_d(dynamic_array);\
        return NULL;\
    } else if (dynamic_array->size == dynamic_array->capacity) {\
        data_type* data = dynamic_array->data;\
        total_memorys_allocated++;\
        triangles_count += dynamic_array->size / 3;\
        free(dynamic_array);\
        return data;\
    } else {\
        data_type* data = realloc(dynamic_array->data, dynamic_array->size * sizeof(data_type));\
        free(dynamic_array);\
        total_memorys_allocated++;\
        triangles_count += dynamic_array->size / 3;\
        return data;\
    }\
}
*/
