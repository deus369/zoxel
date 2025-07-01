// slight refactoring of voxel data
//  -> using type for conversion of allocation
//  -> using allocation for children
//  -> has a type for value, used for cache operations

#define voxel_node_type_closed 0    // air / free
#define voxel_node_type_children 1  // pointing to 8 VoxelNode children
#define voxel_node_type_basic 2     // byte representing a voxel
#define voxel_node_type_entity 3

typedef struct {
    byte value;
} VoxelNodeBasic;

typedef struct {
    ecs_entity_t value;
} VoxelNodeLink;

typedef struct VoxelNode VoxelNode;
struct VoxelNode {
    byte type;
    byte value;
    void *pointer;    // links to a type of struct
};