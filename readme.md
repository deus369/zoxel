# Zoxel

Play Latest [[Here](https://deus369.github.io/zoxel/web/)]

## What is Zoxel?

- An Open Source & Cross-platform Voxel RPG

- Has performance on mushrooms thanks to data orientated design

- Inspired by Minecraft, Warcraft and LitRPGs/Tabletops

- Has a huge [[Roadmap](documents/todos/todo-main.md)] for the future

> See my latest devlog! [[devlog_119](https://www.youtube.com/watch?v=Yb5DiXVt1k0.mp4)]

## Origin Story

Zoxel has been in development a long time. For over a decade, I first made it in Java in 2009.

I have remade it over many different engines, unreal, unity, unity ecs.

The latest iteration was made from 2017 where I added Unitys ECS.

It is time for it to set sail again to a custom game engine, back to my origins!

### Setting Sail

There are 120k+ lines on the unity ecs codebase, so it will take some time for modules to be ported.

So far 12,031 lines have been written, with a great deal of macros to decrease the overall line count.

## Screenshots

New Zoxel (C, FLECS, SDL)

![Le New Zoxel](/documents/screenshots/screen-2022-11-25-18-41-36.jpg?raw=false "Le New Zoxel")

Old Zoxel (Unity Engine ECS)

![Le Old Zoxel](/documents/screenshots/KEyHna.png?raw=false "Le Old Zoxel")

## Links

Try @ itchio [[Le Olde Zoxel](https://deus0.itch.io/zoxel)]

Follow le progress [[Link Tree](https://linktr.ee/lorddeus)]

Code is on [[Codeberg](https://codeberg.org/deus/zoxel)] | [[Github](https://github.com/deus369/zoxel)]

## License

Zoxel is under the GNU General Public License.

I want any derivatives to stay open, to protect the end users and keep information free.

[[The License](license)]

## How To Build

Download the code & use make commands to build it [[How To Build Guide](documents/howtos/howto-build.md)]

### Dependencies

I am using these libraries due to their light weight and power -unlimited power-

- [Flecs](https://github.com/SanderMertens/flecs) Fast and lightweight Entity Component System

- [SDL2](https://www.libsdl.org/index.php) Simple DirectMedia Layer (zlib)

- [OpenGL](https://www.khronos.org/opengles/) OpenGL 3 ES

### Future Libaries

I may switch to Glut in the future to reduce build size even more, instead of SDL.

I may also try out Vulkan, for multi threading powers and performance.