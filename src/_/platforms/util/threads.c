#if zox_windows

byte supports_threads() {
    DWORD id;
    HANDLE t = CreateThread(NULL, 0, (LPTHREAD_START_ROUTINE)ExitThread, NULL, 0, &id);
    if (t == NULL)
        return 0;
    CloseHandle(t);
    return 1;
}

#else

byte supports_threads() {
    return 1;
}

#endif