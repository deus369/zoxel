void Test2System(ecs_iter_t *it) {
    const A *as = ecs_field(it, A, 1);
    const B *bs = ecs_field(it, B, 2);
    C *cs = ecs_field(it, C, 3);
    D *ds = ecs_field(it, D, 4);
    for (int i = 0; i < it->count; i++) {
          const A *a = &as[i];
          const B *b = &bs[i];
          C *c = &cs[i];
          D *d = &ds[i];
          // add your logic here
    }
}
zoxel_declare_system(Test2System)
