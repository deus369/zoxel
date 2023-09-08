//! A basic x2 building block.
typedef struct {
    int x;
    int y;
} int2;

#define int2_zero (int2) { 0, 0 }

unsigned char int2_equals(int2 a, int2 b) {
    return a.x == b.x && a.y == b.y;
}

void int2_add_int2_p(int2 *value, int2 add) {
    value->x += add.x;
    value->y += add.y;
}

void int2_limit(int2 *value, const int2 limits) {
    if (value->x > limits.x) value->x = limits.x;
    else if (value->x < -limits.x) value->x = -limits.x;
    if (value->y > limits.y) value->y = limits.y;
    else if (value->y < -limits.y) value->y = -limits.y;
}

void int2_flip_y(int2 *value, int2 max_value) {
    value->y = max_value.y - value->y;
}

int2 int2_multiply_float(int2 input, float mult) {
    return (int2) { (int) ((float) input.x * mult), (int) ((float) input.y * mult) };
}

int2 int2_multiply_int(int2 input, int mul) {
    return (int2) { input.x * mul, input.y * mul };
}

int2 int2_divide_int(int2 input, int div) {
    return (int2) { input.x / div, input.y / div };
}

int2 int2_add(int2 a, int2 b) {
    return (int2) { a.x + b.x, a.y + b.y };
}

int2 int2_sub(int2 a, int2 b) {
    return (int2) { a.x - b.x, a.y - b.y };
}

unsigned char int2_equal(int2 a, int2 b) {
    return a.x == b.x && a.y == b.y;
}

int int2_distance(int2 a, int2 b) {
    return sqrt((a.x - b.x) * (a.x - b.x) + (a.y - b.y) * (a.y - b.y));
    /*int2 o = int2_sub(a, b);
    if (o.x < 0)
    {
        o.x = -o.x;
    }
    if (o.y < 0)
    {
        o.y = -o.y;
    }
    return o.x + o.y;*/
}

int2 int2_normalize(int2 input) {
    int length = (int) ceil(sqrt(input.x * input.x + input.y * input.y));
    return int2_divide_int(input, length);
}

int int2_array_index(int2 input, int2 size) {
    return input.x + input.y * size.x;
}

int int2_array_index2(int2 input, int2 size) {
    return input.y + input.x * size.x;
}
// return input.y + input.x * size.y;

int2 get_from_byte2(byte2 input) {
    return (int2) { (int) input.x, (int) input.y };
}

int2 int2_down(int2 input) {
    return (int2) { input.x, input.y - 1 };
}

int2 int2_up(int2 input) {
    return (int2) { input.x, input.y + 1 };
}

int2 int2_left(int2 input) {
    return (int2) { input.x - 1, input.y };
}

int2 int2_right(int2 input) {
    return (int2) { input.x + 1, input.y };
}

unsigned char int2_in_bounds(int2 input, int2 size) {
    return (input.x >= 0 && input.x < size.x
        && input.y >= 0 && input.y < size.y);
}

float float_clamp(float input, float x, float y) {
    if (input < x)
    {
        return x;
    }
    else if (input > y)
    {
        return y;
    }
    else
    {
        return input;
    }
}

int int_clamp(int input, int x, int y) {
    if (input < x)
    {
        return x;
    }
    else if (input > y)
    {
        return y;
    }
    else
    {
        return input;
    }
}