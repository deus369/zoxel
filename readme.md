# Libre Zoxel

Play Zoxel ([here](https://deus369.github.io/open-zoxel/web-demo/))

Open Source & Cross-platform + Performance is on Mushrooms~

Open-Zoxel is under the GPL license as I want any derivatives to stay open, to protect the end users and keep information free.

Zoxel has a large scope as I have many ideas. It's game design is influenced from Minecraft, Warcraft and LitRPGs/Tabletops.

## How far along is it?

So far I am fleshing out basic systems while testing out Flecs useage. So far the performance has been promising!

My Task list! [Todo Lists](Documents/todos/todo-main.md)

Check out my latest short dev log on YouTube!

[![Open Zoxel](http://img.youtube.com/vi/Yb5DiXVt1k0/0.jpg)](https://www.youtube.com/watch?v=Yb5DiXVt1k0.mp4 "Open Zoxel")

## Why The Change?

Zoxel has been in development a long time (over a decade), over many different engines. It is time for it to set sail again to a custom one, using FLECS for performance! The latest iteration was made from 2017 where I added Unitys ECS.

This was not an easy decision. Gotta go fast! Flecs has offered me a way out of the Unity IPO mess, and it offers greater levels of freedom over my development.

There are 120k+ lines on the unity ecs codebase, so it will take some time for things to be ported.

Try Le old Zoxel ([here](https://deus0.itch.io/zoxel))

![Le Old Zoxel](/Screenshots/KEyHna.png?raw=false "Le Old Zoxel")

## How To Build

After you download the repo, you can use Make commands to build it!

[How To Build Guide](Documents/howtos/howto-build.md)

### Dependencies

I am using these libraries due to their light weight and power -unlimited power-

[Flecs](https://github.com/SanderMertens/flecs) Fast and lightweight Entity Component System

[SDL2](https://www.libsdl.org/index.php) Simple DirectMedia Layer (zlib)

[OpenGL](https://www.khronos.org/opengles/) OpenGL 3 ES

I may switch to Glut in the future to reduce build size even more, instead of SDL. I may also try out Vulkan.