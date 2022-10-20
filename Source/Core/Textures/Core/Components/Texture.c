// #include <cstdint> ? https://stackoverflow.com/questions/20024690/is-there-byte-data-type-in-c
/*
You could use the same change tracking feature that you've used before
If the Texture field is inout/out, it will automatically get flagged as dirty when you iterate it
Then in a system/query that reads the texture, you can use ecs_query_changed
*/

//! \todo Make this into a Macro for Memory Array Components.

//! A texture with pixels!
typedef struct
{
    color *value;
    int length;
} Texture;
ECS_COMPONENT_DECLARE(Texture);

void initialize_texture(Texture *texture, int length)
{
    /*if (texture->value)
    {
        free(texture->value);
    }*/
    const int stride = sizeof(color);
    texture->length = length;
    texture->value = malloc(length * stride);
}

//! The constructor should initialize the component value.
ECS_CTOR(Texture, ptr,
{
    // ecs_trace("Ctor");
    ptr->value = NULL;
})

//! The destructor should free resources.
ECS_DTOR(Texture, ptr,
{
    printf("Destroying Texture Memory.\n");
    // printf("ECS_DTOR: Disposing view matrix [%f] \n", ptr->value[0]); // ecs_trace("Dtor");
    if (ptr->value)
    {
        free(ptr->value);
        printf("Destroying Texture Memory.\n");
    }
})

//! Copy a pointer from one component to another.
ECS_MOVE(Texture, dst, src,
{
    free(dst->value);
    dst->value = src->value;
    src->value = NULL;
})

//! Copy one data block to another.
ECS_COPY(Texture, dst, src,
{
    // printf("Copying Data.");
    if (src->value)
    {
        int memoryLength = src->length; // 16 * 16 * 4;
        free(dst->value);
        dst->value = malloc(memoryLength);
        if (dst->value != NULL) 
        {
            dst->value = memcpy(dst->value, src->value, memoryLength);
        }
    }
})