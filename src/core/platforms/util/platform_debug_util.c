unsigned char is_steam_deck() {
    if (getenv("STEAMOS_SESSIONTYPE") != NULL && strcmp(getenv("STEAMOS_SESSIONTYPE"), "steam") == 0) {
        return 1;
    } else {
        return 0;
    }
}

void debug_platform() {
#if defined(zoxel_on_android)
    zox_log(" > platform [android]\n")
#elif defined(zoxel_on_windows)
    zox_log(" > platform [windows]\n")
#elif defined(zoxel_on_web)
    zox_log(" > platform [web]\n")
#elif defined(zoxel_on_linux)
    zox_log(" > platform [linux]\n")
#endif
#if defined(zoxel_on_steamdeck)
    zox_log(" > platform [steamdeck]\n")
#endif
    if (is_steam_deck()) {
        zox_log(" > platform [steamdeck] (check 2)\n")
    }
}

// char* wine_prefix = getenv("WINEPREFIX");

unsigned char is_platform_wine() {
#ifdef zoxel_on_windows
    return 0;
#else
    return 0;
    /*static const char *(CDECL *pwine_get_version)(void);
    HMODULE hntdll = GetModuleHandle("ntdll.dll");
    if(!hntdll)
    {
        puts("Not running on NT.");
        return 1;
    }
    pwine_get_version = (void *) GetProcAddress(hntdll, "wine_get_version");
    return (pwine_get_version);*/
    // printf("Running on Wine... %s\n",pwine_get_version());
#endif
    /*const char* wine_prefix = getenv("WINEARCH");
    zox_log("   wine_prefix [%s]\n", wine_prefix)
    return (wine_prefix != NULL);*/
}
