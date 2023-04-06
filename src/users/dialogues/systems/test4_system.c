void Test4System(ecs_iter_t *it) {
    const Peter *peters = ecs_field(it, Peter, 1);
    const Pan *pans = ecs_field(it, Pan, 2);
    Jonny *jonnys = ecs_field(it, Jonny, 3);
    Joes *joess = ecs_field(it, Joes, 4);
    for (int i = 0; i < it->count; i++) {
          const Peter *peter = &peters[i];
          const Pan *pan = &pans[i];
          Jonny *jonny = &jonnys[i];
          Joes *joes = &joess[i];
          // add your logic here
    }
}
zoxel_declare_system(Test4System)
