
//! Destroy SDLWindow.
ECS_DTOR(SDLWindow, ptr,
{
    if (ptr->value != 0)
    {
        SDL_DestroyWindow(ptr->value);
    }
})

//! Destroy SDL Renderer.
ECS_DTOR(Renderer, ptr,
{
    if (ptr->value != 0)
    {
        SDL_DestroyRenderer(ptr->value);
    }
})
//! Destroy SDL Context.
ECS_DTOR(Context, ptr,
{
    if (ptr->value != 0)
    {
        SDL_GL_DeleteContext(ptr->value);
    }
})