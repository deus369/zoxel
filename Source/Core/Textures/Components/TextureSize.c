// #include <cstdint> ? https://stackoverflow.com/questions/20024690/is-there-byte-data-type-in-c
//! A texture with pixels!
typedef struct
{
    int2 value;
} TextureSize;
ECS_COMPONENT_DECLARE(TextureSize);