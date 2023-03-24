// profiling: make build/dev && make run-dev-profiler
// #include "profiler_defines.c"
#include "zoxel_engine.c"
#include "zoxel/zoxel.c"

#ifdef ANDROID_BUILD
    #include <android/log.h>
    #define APPNAME "Zoxel"
#endif

#ifdef WINDOWS_BUILD
int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow) {
    int argc = 0;
    char** argv = NULL;
#else
int main(int argc, char* argv[]) {
#endif
    #ifdef ANDROID_BUILD
        // __android_log_set_output(ANDROID_LOG_OUTPUT_STDOUT);
        /*char log_file_path[1024];
        snprintf(log_file_path, sizeof(log_file_path), "/sdcard/%s.log", APPNAME);
        android_log_set_output(ANDROID_LOG_OUTPUT_FILE, log_file_path);*/

        int result = __android_log_print(ANDROID_LOG_VERBOSE, APPNAME, "%s", "Main function of zoxel.");
        if (result < 0) {
            int error = errno;
            fprintf(stderr, "Error printing log message: %s\n", strerror(error));
        }
        __android_log_print(ANDROID_LOG_VERBOSE, APPNAME, "%s", "Main function of zoxel.");
    #endif
    //! Where it all begins and ends.
    if (begin(argc, argv) == EXIT_SUCCESS) {
        zoxel_import_module(Zoxel)       // import game
        main_loop();
        end();
    }
    return 0;
}