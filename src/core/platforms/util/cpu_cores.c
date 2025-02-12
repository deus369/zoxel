byte get_cpu_count() {
    #if defined(__EMSCRIPTEN__)
        int cores = emscripten_get_num_cores();
        return cores > 0 ? (byte) cores : 1;
    #elif defined(_WIN32) || defined(_WIN64)
        SYSTEM_INFO sysinfo;
        GetSystemInfo(&sysinfo);
        return (byte) sysinfo.dwNumberOfProcessors;
    #elif defined(_SC_NPROCESSORS_ONLN)
        long nprocs = sysconf(_SC_NPROCESSORS_ONLN);
        return (nprocs < 1 ? 1 : (byte) nprocs);
    #else
        return 1;
    #endif
}
