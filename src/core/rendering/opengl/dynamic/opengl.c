
#define OPENGL_FUNCTIONS                                                            \
    OPENGL_FUNCTION(glCreateShader, PFNGLCREATESHADERPROC)                          \
    OPENGL_FUNCTION(glDeleteShader, PFNGLDELETESHADERPROC)                          \
    OPENGL_FUNCTION(glAttachShader, PFNGLATTACHSHADERPROC)                          \
    OPENGL_FUNCTION(glDetachShader, PFNGLDETACHSHADERPROC)                          \
    OPENGL_FUNCTION(glShaderSource, PFNGLSHADERSOURCEPROC)                          \
    OPENGL_FUNCTION(glCompileShader, PFNGLCOMPILESHADERPROC)                        \
    OPENGL_FUNCTION(glGetShaderiv, PFNGLGETSHADERIVPROC)                            \
    OPENGL_FUNCTION(glGetShaderInfoLog, PFNGLGETSHADERINFOLOGPROC)                  \
    OPENGL_FUNCTION(glCreateProgram, PFNGLCREATEPROGRAMPROC)                        \
    OPENGL_FUNCTION(glDeleteProgram, PFNGLDELETEPROGRAMPROC)                        \
    OPENGL_FUNCTION(glUseProgram, PFNGLUSEPROGRAMPROC)                              \
    OPENGL_FUNCTION(glLinkProgram, PFNGLLINKPROGRAMPROC)                            \
    OPENGL_FUNCTION(glValidateProgram, PFNGLVALIDATEPROGRAMPROC)                    \
    OPENGL_FUNCTION(glGetProgramiv, PFNGLGETPROGRAMIVPROC)                          \
    OPENGL_FUNCTION(glGetProgramInfoLog, PFNGLGETPROGRAMINFOLOGPROC)                \
    OPENGL_FUNCTION(glUniform1i, PFNGLUNIFORM1IPROC)                                \
    OPENGL_FUNCTION(glUniform1f, PFNGLUNIFORM1FPROC)                                \
    OPENGL_FUNCTION(glUniform2f, PFNGLUNIFORM2FPROC)                                \
    OPENGL_FUNCTION(glUniform3f, PFNGLUNIFORM3FPROC)                                \
    OPENGL_FUNCTION(glUniform4f, PFNGLUNIFORM4FPROC)                                \
    OPENGL_FUNCTION(glUniformMatrix4fv, PFNGLUNIFORMMATRIX4FVPROC)                  \
    OPENGL_FUNCTION(glGenBuffers, PFNGLGENBUFFERSPROC)                              \
    OPENGL_FUNCTION(glDeleteBuffers, PFNGLDELETEBUFFERSPROC)                        \
    OPENGL_FUNCTION(glBindBuffer, PFNGLBINDBUFFERPROC)                              \
    OPENGL_FUNCTION(glBufferData, PFNGLBUFFERDATAPROC)                              \
    OPENGL_FUNCTION(glVertexAttribPointer, PFNGLVERTEXATTRIBPOINTERPROC)            \
    OPENGL_FUNCTION(glEnableVertexAttribArray, PFNGLENABLEVERTEXATTRIBARRAYPROC)    \
    OPENGL_FUNCTION(glDisableVertexAttribArray, PFNGLDISABLEVERTEXATTRIBARRAYPROC)  \
    OPENGL_FUNCTION(glBufferSubData, PFNGLBUFFERSUBDATAPROC)                        \
    OPENGL_FUNCTION(glGetAttribLocation, PFNGLGETATTRIBLOCATIONPROC)                \
    OPENGL_FUNCTION(glIsProgram, PFNGLISPROGRAMPROC)                                

    // OPENGL_FUNCTION(glGetUniformLocation, PFNGLGETUNIFORMLOCATIONPROC) 
    // OPENGL_FUNCTION(glGetUniformLocation, PFNGLGETUNIFORMLOCATIONPROC)
    // OPENGL_FUNCTION(glBindVertexArray, PFNGLBINDVERTEXARRAYPROC)
    // OPENGL_FUNCTION(glDeleteVertexArrays, PFNGLDELETEVERTEXARRAYSPROC)
    // OPENGL_FUNCTION(glGenVertexArrays, PFNGLGENVERTEXARRAYSPROC)

#define OPENGL_DECLARE(func_name, func_type)  \
    extern func_type func_name;

#define OPENGL_FUNCTION OPENGL_DECLARE
OPENGL_FUNCTIONS
#undef OPENGL_FUNCTION

unsigned char opengl_load_functions(void);

// #endif

#define OPENGL_DEFINE(func_name, func_type)  \
    func_type func_name __attribute__((weak))  = NULL;

#define OPENGL_FUNCTION OPENGL_DEFINE
OPENGL_FUNCTIONS
#undef OPENGL_FUNCTION

union bridge
{
    void* object_ptr;
    void (*function_ptr)(void);
};

#define OPENGL_LOAD(func_name, func_type)                \
    func_name = (func_type)(union bridge)               \
    {               \
        .object_ptr = SDL_GL_GetProcAddress(#func_name)  \
    }.function_ptr;

#define OPENGL_VALIDATE(func_name, func_type)                      \
    if (func_name == NULL) {                                       \
        fprintf(stderr, "failed to load func: %s\n", #func_name);  \
        return false;                                              \
    }

#define opengl_define_function(func_type, func_name)  \
    func_type func_name __attribute__((weak)) = NULL;

#define opengl_load_function(func_type, func_name)          \
    func_name = (func_type)(union bridge)                   \
    {                                                       \
        .object_ptr = SDL_GL_GetProcAddress(#func_name)     \
    }.function_ptr;                                         \
    if (func_name == NULL)                                  \
    {                                                       \
        fprintf(stderr, "failed to load func: %s\n", #func_name);  \
        return false;                                        \
    }

opengl_define_function(PFNGLGETUNIFORMLOCATIONPROC, glGetUniformLocation)

unsigned char opengl_load_functions(void)
{
    opengl_load_function(PFNGLGETUNIFORMLOCATIONPROC, glGetUniformLocation)

    #define OPENGL_FUNCTION OPENGL_LOAD
OPENGL_FUNCTIONS
    #undef OPENGL_FUNCTION

    #define OPENGL_FUNCTION OPENGL_VALIDATE
OPENGL_FUNCTIONS
    #undef OPENGL_FUNCTION

    return 1;
}