# Zoxel El Libre

~ Play Latest [[Web Build](https://deus369.github.io/zoxel/web-demo/)] ~

## What is Zoxel?

> See my latest devlog! [[devlog_119](https://www.youtube.com/watch?v=Yb5DiXVt1k0.mp4)]

- An Open Source & Cross-platform Voxel RPG

- Is inspired by Minecraft, Warcraft and LitRPGs/Tabletops

- Has performance on mushrooms thanks to data orientated design

- Under the GPL license! (I want any derivatives to stay open, to protect the end users and keep information free)

- Has a huge roadmap for the future [[Roadmap](documents/todos/todo-main.md)]

![Le New Zoxel](/screenshots/screen-2022-11-25-18-41-36.jpg?raw=false "Le New Zoxel")

## How To Build

> Download the code & use make commands to build it

Build Zoxel! [[How To Build?](documents/howtos/howto-build.md)]

See some statistics [[Code Counter](documents/CodeCounter/results.md)]

### Dependencies

I am using these libraries due to their light weight and power -unlimited power-

- [Flecs](https://github.com/SanderMertens/flecs) Fast and lightweight Entity Component System

- [SDL2](https://www.libsdl.org/index.php) Simple DirectMedia Layer (zlib)

- [OpenGL](https://www.khronos.org/opengles/) OpenGL 3 ES

I may switch to Glut in the future to reduce build size even more, instead of SDL. I may also try out Vulkan.

## Why The Change?

Zoxel has been in development a long time. For over a decade, I first made it in Java in 2009.

I have remade it over many different engines, unreal, unity, unity ecs. The latest iteration was made from 2017 where I added Unitys ECS.

It is time for it to set sail again to a custom one, using FLECS for performance!

### ~ = ~ Setting Sail ~ = ~

This was not an easy decision. Flecs has offered me a way out of the Unity IPO mess, and it offers greater levels of freedom over my development.

There are 120k+ lines on the unity ecs codebase, so it will take some time for things to be ported.

Try @ itchio [[Le Olde Zoxel](https://deus0.itch.io/zoxel)]

Follow le progress [[Link Tree](https://linktr.ee/lorddeus)]

![Le Old Zoxel](/screenshots/KEyHna.png?raw=false "Le Old Zoxel")

### Mirrored

Code is on [[Codeberg](https://codeberg.org/deus/zoxel)] | [[Github](https://github.com/deus369/zoxel)].