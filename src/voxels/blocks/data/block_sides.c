#define block_side_left 0
#define block_side_right 1
#define block_side_down 2
#define block_side_up 3
#define block_side_back 4
#define block_side_front 5

byte byte3_on_edge_axis(const byte3 pos, const byte3 size, const byte axis) {
    return (axis == block_side_left && pos.x == 0) ||
        (axis == block_side_down && pos.y == 0) ||
        (axis == block_side_back && pos.z == 0) ||
        (axis == block_side_right && pos.x == size.x - 1) ||
        (axis == block_side_up && pos.y == size.y - 1) ||
        (axis == block_side_front && pos.z == size.z - 1);
}
