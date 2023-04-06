void TestSystem(ecs_iter_t *it) {
    const Hi *his = ecs_field(it, Hi, 1);
    const There *theres = ecs_field(it, There, 2);
    Peter *peters = ecs_field(it, Peter, 3);
    Pan *pans = ecs_field(it, Pan, 4);
    for (int i = 0; i < it->count; i++) {
          const Hi *hi = &his[i];
          const There *there = &theres[i];
          Peter *peter = &peters[i];
          Pan *pan = &pans[i];
          // add your logic here
    }
}
zoxel_declare_system(TestSystem)
