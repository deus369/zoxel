typedef struct {
    ecs_query_t *x;
    ecs_query_t *y;
} ctx2;

#define zox_filter_combine(name, filter1, filter2)\
    name = (ctx2) { filter1, filter2 };
