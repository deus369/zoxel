To-Do Main
-----

[Back](../../readme.md)

-----

`Documentation`
- [ ] Look into docs forge (https://github.com/engine99team/engine99)

`Flecs Testing`
- [ ] DestroyEntity event and systems, with disposing of allocations (OnDelete events?)
    - [ ] DestroyInTimeSystem
- [ ] Add variables to profiler
    - https://github.com/SanderMertens/flecs/blob/master/examples/c/reflection/basics/src/main.c
- [ ] Binary serializer for data
- [x] Find a better way to add new systems and components per module - organized
- [x] Try out prefabs and mass spawning / data setting
    - [x] Spawn System
- [x] Inject data into another system
- [x] Seperate out shaders from inlines
    - [ ] Find a way to package shaders into binary build
- [x] Nativearray data structure
    - can just use malloc
- [ ] Customize flecs to remove some feaures to reduce build size
- [ ] Why did i have to comment these out
    nanosleep getnameinfo CLOCK_MONOTONIC clock_gettime NI_NUMERICHOST NI_NUMERICSERV
- [ ] Multithreading / non multi threading not supported yet
    https://github.com/SanderMertens/Imports/Flecs/issues/798
- [ ] Make OpenGLUtil one file
- [ ] const ecs_field not available yet
    'You can assign it to a const, but I haven't yet added const checking to the C API'

`Input`
- [x] Convert SDL of keyboard into an entity
- [ ] Find a Library that supports multiple (keyboard or otherwise) devices

`Application Side`
- [ ] Support multiple Windows.

`Done`

- [x] Seperate out structs into component files