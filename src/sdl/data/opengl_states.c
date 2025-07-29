// different opengl modes with sdl
#define zox_opengl_core 0
#define zox_opengl_es 1
#define zox_opengl_compatibility 2

byte override_opengl_es = 0;
#ifdef __ANDROID__
    byte opengl_mode = zox_opengl_es;
    byte sdl_gl_major = 3;
    byte sdl_gl_minor = 0;
    ushort shader_opengl_version = 300;
#else
    byte opengl_mode = zox_opengl_es;
    byte sdl_gl_major = 3;
    byte sdl_gl_minor = 0;
    ushort shader_opengl_version = 300;
    /*byte opengl_mode = zox_opengl_core;
    byte sdl_gl_major = 4;
    byte sdl_gl_minor = 6;
    ushort shader_opengl_version = 460;*/
#endif
