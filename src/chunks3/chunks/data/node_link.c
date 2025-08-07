
// slight refactoring of voxel data
//  -> using type for conversion of allocation
//  -> using allocation for children
//  -> has a type for value, used for cache operations

/*typedef struct {
    byte value;
} VoxelNodeBasic;

typedef struct {
    entity value;
} VoxelNodeLink;

typedef struct VoxelNode VoxelNode;
struct VoxelNode {
    byte type;
    byte value;
    void *pointer;    // links to a type of struct
};*/