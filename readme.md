# Zoxel (Libre Edition)

Play [[Web Build](https://deus369.github.io/open-zoxel/web-demo/)]

See [[Roadmap](documents/todos/todo-main.md)]

Numbers [[Code Counter](documents/CodeCounter/results.md)]

## What is Zoxel?

> See my latest dev log on youtube [[devlog_119](https://www.youtube.com/watch?v=Yb5DiXVt1k0.mp4)]

- And Open Source, Cross-platform Voxel RPG

- With performance is on mushrooms thanks to data orientated design

- Under the GPL license! (I want any derivatives to stay open, to protect the end users and keep information free)

- Has a huge roadmap for the future

- Is inspired by Minecraft, Warcraft and LitRPGs/Tabletops

![Le New Zoxel](/screenshots/screenshot_2022-11-04_18-56-29.png?raw=false "Le New Zoxel")

## How To Build

> Download the code & use make commands to build it!

Build Zoxel [How To Build?](documents/howtos/howto-build.md)

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

### ~Setting Sail~

This was not an easy decision. Flecs has offered me a way out of the Unity IPO mess, and it offers greater levels of freedom over my development.

There are 120k+ lines on the unity ecs codebase, so it will take some time for things to be ported.

Try @ ItchIO [[Le Olde Zoxel](https://deus0.itch.io/zoxel)]

Follow My Progress [[Link Tree](https://linktr.ee/lorddeus)]

![Le Old Zoxel](/screenshots/KEyHna.png?raw=false "Le Old Zoxel")