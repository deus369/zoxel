union bridge
{
    void* object_ptr;
    void (*function_ptr)(void);
};

#define GL_GLEXT_PROTOTYPES

// loads all these functions
#define opengl_functions                                                            \
    opengl_function(glCreateShader, PFNGLCREATESHADERPROC)                          \
    opengl_function(glDeleteShader, PFNGLDELETESHADERPROC)                          \
    opengl_function(glAttachShader, PFNGLATTACHSHADERPROC)                          \
    opengl_function(glDetachShader, PFNGLDETACHSHADERPROC)                          \
    opengl_function(glShaderSource, PFNGLSHADERSOURCEPROC)                          \
    opengl_function(glCompileShader, PFNGLCOMPILESHADERPROC)                        \
    opengl_function(glGetShaderiv, PFNGLGETSHADERIVPROC)                            \
    opengl_function(glGetShaderInfoLog, PFNGLGETSHADERINFOLOGPROC)                  \
    opengl_function(glCreateProgram, PFNGLCREATEPROGRAMPROC)                        \
    opengl_function(glDeleteProgram, PFNGLDELETEPROGRAMPROC)                        \
    opengl_function(glUseProgram, PFNGLUSEPROGRAMPROC)                              \
    opengl_function(glLinkProgram, PFNGLLINKPROGRAMPROC)                            \
    opengl_function(glValidateProgram, PFNGLVALIDATEPROGRAMPROC)                    \
    opengl_function(glGetProgramiv, PFNGLGETPROGRAMIVPROC)                          \
    opengl_function(glGetProgramInfoLog, PFNGLGETPROGRAMINFOLOGPROC)                \
    opengl_function(glUniform1i, PFNGLUNIFORM1IPROC)                                \
    opengl_function(glUniform1f, PFNGLUNIFORM1FPROC)                                \
    opengl_function(glUniform2f, PFNGLUNIFORM2FPROC)                                \
    opengl_function(glUniform3f, PFNGLUNIFORM3FPROC)                                \
    opengl_function(glUniform4f, PFNGLUNIFORM4FPROC)                                \
    opengl_function(glUniformMatrix4fv, PFNGLUNIFORMMATRIX4FVPROC)                  \
    opengl_function(glGenBuffers, PFNGLGENBUFFERSPROC)                              \
    opengl_function(glDeleteBuffers, PFNGLDELETEBUFFERSPROC)                        \
    opengl_function(glBindBuffer, PFNGLBINDBUFFERPROC)                              \
    opengl_function(glBufferData, PFNGLBUFFERDATAPROC)                              \
    opengl_function(glVertexAttribPointer, PFNGLVERTEXATTRIBPOINTERPROC)            \
    opengl_function(glEnableVertexAttribArray, PFNGLENABLEVERTEXATTRIBARRAYPROC)    \
    opengl_function(glDisableVertexAttribArray, PFNGLDISABLEVERTEXATTRIBARRAYPROC)  \
    opengl_function(glBufferSubData, PFNGLBUFFERSUBDATAPROC)                        \
    opengl_function(glGetAttribLocation, PFNGLGETATTRIBLOCATIONPROC)                \
    opengl_function(glIsProgram, PFNGLISPROGRAMPROC)                                \
    opengl_function(glGetUniformLocation, PFNGLGETUNIFORMLOCATIONPROC)              \
    opengl_function(glDispatchCompute, PFNGLDISPATCHCOMPUTEPROC)                    \
    opengl_function(glGetIntegeri_v, PFNGLGETINTEGERI_VPROC)

#define opengl_declare(func_name, func_type)    \
    func_type func_name __attribute__((weak))  = NULL;

#define opengl_load_function(func_name, func_type)                  \
    func_name = (func_type)(union bridge)                           \
    {                                                               \
        .object_ptr = SDL_GL_GetProcAddress(#func_name)             \
    }.function_ptr;                                                 \
    if (func_name == NULL)                                          \
    {                                                               \
        fprintf(stderr, "failed to load func: %s\n", #func_name);   \
        return false;                                               \
    }


#define opengl_function opengl_declare
    opengl_functions
#undef opengl_function

unsigned char opengl_load_functions()
{
    #define opengl_function opengl_load_function
        opengl_functions
    #undef opengl_functions
    return 1;
}