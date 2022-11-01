To-Do Done
-----

Things that are done.

[Back](todo-main.md)

-----

`Done`
- [x] Push UV into Textured Material
    - [x] Use minimal example for drawing with uvs?
- [x] Material Comonent - with a GLInt reference to a material
- [x] Link texture data in material
- [x] Convert SDL of keyboard into an entity
- [x] Seperate out structs into component files
- [x] DestroyEntity event and systems, with disposing of allocations (OnDelete events?)
    - [x] DestroyInTimeSystem
    - Flecs had a great way to handle memory allocations
- [x] Find a better way to add new systems and components per module - organized
- [x] Try out prefabs and mass spawning / data setting
    - [x] Spawn System
- [x] Inject data into another system
- [x] Seperate out shaders from inlines
    - [ ] Find a way to package shaders into binary build
- [x] Nativearray data structure
    - can just use malloc
- [x] Customize flecs to remove some feaures to reduce build size
- [x] Why did i have to comment these out
    nanosleep getnameinfo CLOCK_MONOTONIC clock_gettime NI_NUMERICHOST NI_NUMERICSERV
    - they are non c99 codes
- [x] A single threaded system will not run on main thread
    - Follow this up
    https://github.com/SanderMertens/Imports/Flecs/issues/798
- [x] const ecs_field not available yet
    'You can assign it to a const, but I haven't yet added const checking to the C API'