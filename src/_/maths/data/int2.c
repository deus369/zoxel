#define int2_zero (int2) { 0, 0 }
#define int2_one (int2) { 1, 1 }
#define int2_two (int2) { 2, 2 }
#define int2_four (int2) { 4, 4 }
#define int2_hidden (int2) { -666, -666 }   // used for canvas position

static inline int2 int2_half(const int2 value) {
    return (int2) { value.x / 2, value.y / 2 };
}

static inline int2 int2_scalef(const int2 value, const float f) {
    return (int2) { (int) (value.x * f), (int) (value.y * f) };
}

static inline int2 int2_single(const int value) {
    return (int2) { value, value };
}

static inline byte int2_equals(const int2 a, const int2 b) {
    return a.x == b.x && a.y == b.y;
}

void int2_add_int2_p(int2 *value, const int2 add) {
    value->x += add.x;
    value->y += add.y;
}

static inline void int2_sub_int2(int2 *value, const int2 add) {
    value->x -= add.x;
    value->y -= add.y;
}

static inline int2 int2_sub_int2_(const int2 a, const int2 b) {
    return (int2) { a.x - b.x, a.y - b.y };
}

static inline void int2_limit(int2 *value, const int2 limits) {
    if (value->x > limits.x) value->x = limits.x;
    else if (value->x < -limits.x) value->x = -limits.x;
    if (value->y > limits.y) value->y = limits.y;
    else if (value->y < -limits.y) value->y = -limits.y;
}

static inline void int2_flip_y(int2 *value, const int2 max_value) {
    value->y = max_value.y - value->y;
}

static inline int2 int2_multiply_float(const int2 input, const float mult) {
    return (int2) { (int) ((float) input.x * mult), (int) ((float) input.y * mult) };
}

static inline int2 int2_multiply_int(const int2 input, const int mul) {
    return (int2) { input.x * mul, input.y * mul };
}

int2 int2_divide_int(const int2 input, const int div) {
    return (int2) { input.x / div, input.y / div };
}

static inline int2 int2_add(const int2 a, const int2 b) {
    return (int2) { a.x + b.x, a.y + b.y };
}

static inline int2 int2_sub(const int2 a, const int2 b) {
    return (int2) { a.x - b.x, a.y - b.y };
}

static inline void int2_add_p(int2 *a, const int2 b) {
    a->x += b.x;
    a->y += b.y;
}

static inline void int2_subtract(int2 *a, const int2 b) {
    a->x -= b.x;
    a->y -= b.y;
}

static inline void int2_divide_int_p(int2 *a, const int div) {
    a->x /= div;
    a->y /= div;
}

static inline int int2_max(const int2 value) {
    if (value.x >= value.y) return value.x;
    else return value.y;
}

static inline int int2_min(const int2 value) {
    if (value.x <= value.y) return value.x;
    else return value.y;
}

static inline byte int2_equal(const int2 a, const int2 b) {
    return a.x == b.x && a.y == b.y;
}

static inline int int2_distance(const int2 a, const int2 b) {
    return sqrt((a.x - b.x) * (a.x - b.x) + (a.y - b.y) * (a.y - b.y));
}

static inline int2 int2_normalize(const int2 input) {
    int length = (int) ceil(sqrt(input.x * input.x + input.y * input.y));
    return int2_divide_int(input, length);
}

static inline int int2_array_index(const int2 input, const int2 size) {
    return input.x + input.y * size.x;
}

static inline int int2_array_index2(const int2 input, const int2 size) {
    return input.y + input.x * size.x;
}

static inline int2 int2_down(const int2 input) {
    return (int2) { input.x, input.y - 1 };
}

static inline int2 int2_up(const int2 input) {
    return (int2) { input.x, input.y + 1 };
}

static inline int2 int2_left(const int2 input) {
    return (int2) { input.x - 1, input.y };
}

static inline int2 int2_right(const int2 input) {
    return (int2) { input.x + 1, input.y };
}

static inline byte int2_in_bounds(const int2 input, const int2 size) {
    return (input.x >= 0 && input.x < size.x
        && input.y >= 0 && input.y < size.y);
}