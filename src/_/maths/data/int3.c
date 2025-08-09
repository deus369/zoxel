static const int3 int3_zero     = { 0, 0, 0 };
static const int3 int3_chaos    = { -666, -666, -666 };
static const int3 int3_left     = { -1, 0, 0 };
static const int3 int3_right    = {  1, 0, 0 };
static const int3 int3_down     = {  0, -1, 0 };
static const int3 int3_up       = {  0, 1, 0 };
static const int3 int3_backward = {  0, 0, -1 };
static const int3 int3_forward  = {  0, 0, 1 };

const int3 int3_directions[] = {
    int3_left,
    int3_right,
    int3_down,
    int3_up,
    int3_backward,
    int3_forward
};
