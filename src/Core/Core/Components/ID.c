//! An entity can have a unique ID generated by guid or something.
typedef struct
{
    int value;
} ID;
ECS_COMPONENT_DECLARE(ID);