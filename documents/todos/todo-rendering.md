To-Do Rendering
-----

Atm is uses OpenGL, perhaps I can support Vulkan in the future?

[Back](todo-main.md)

-----

`Current`

- [ ] Fix Render Ordering
    - fps display breaks it, due to reordering of flecs tables
    - add a big array of things to render, resize array if game uses more
    - set this array per frame inside ecs, then in render systems render it
    - reorder the list into a second one, based on layyers of ui, position from camera
    - depth for camera?

-----

`Rendering`
- [ ] Mesh Component - for unique mesh (maybe later i can scale uis in shader?)
- [ ] BasicRenderSystem - renders unique mesh / materials
- [ ] Support for Unique Mesh / Square Mesh (instance vertex data)
- [ ] Write a dynamic material / shader system
    - [ ] shader manager singleton
    - [ ] load list of shaders instead of specific
    - [ ] Handle properties better? do I need all that location reference..?

`Refactoring`
- [ ] Make opengl.c/h one file, it imports in functions