const uint max_safety_checks_hashmap = 1024;
#ifndef zox_windows
    const byte hashmap_safety_locks = 1;
    const byte nodes_w_safety_locks = 1;
    const byte nodes_r_safety_locks = 1;
#else
    const byte hashmap_safety_locks = 0;
    const byte nodes_w_safety_locks = 0;
    const byte nodes_r_safety_locks = 0;
#endif