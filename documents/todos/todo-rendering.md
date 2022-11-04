To-Do Rendering
-----

Atm is uses OpenGL, perhaps I can support Vulkan in the future?

[Back](todo-main.md)

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