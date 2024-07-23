// profiling: make build/dev && make run-dev-profiler
#include "zox/zox.c"
#include zox_nexus_game

#ifdef zoxel_on_windows
int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow) {
    int argc = 0;
    char** argv = NULL;
#else
int main(int argc, char* argv[]) {
#endif
    ecs_world_t *world = initialize_ecs(argc, argv);
    if (world == NULL) {
        zox_log(" ! engine failed to start\n")
        return 0;
    }
    zox_import_module(Zox)
#ifdef zox_mod_game
    zox_import_module(ZoxGame)
#else
    zox_log(" ! game not loaded\n")
#endif
    if (boot_event(world) == EXIT_SUCCESS) update_zox();
    else zox_log(" ! booting zoxel failed\n")
    dispose_zox(world);
    return 0;
}
