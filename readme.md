# Zoxel

> Play Latest [[Here](https://deus369.github.io/zoxel/web/)]

> See My Devlog! [[devlog_119](https://www.youtube.com/watch?v=Yb5DiXVt1k0.mp4)]

> My Current Tasks [[Tasks](documents/todos/todo-main.md)]

## What is Zoxel?

- A First Person Voxel RPG

- Inspired by Minecraft, Warcraft and LitRPGs/Tabletops

- Open Source (GPL) & Cross-platform (Linux, Windows*, Android, Web, IOS*)

- Great performance due to data orientated design

- Future Forward [[Roadmap](documents/roadmap.md)]

## Origin Story

Zoxel has been in development a long time. For over a decade, I first made it in Java in 2009.

I have remade it over many different engines, unreal, unity, unity ecs.

The last iteration was made 2017-2022 where I added Unitys ECS.

It is time for it to set sail again to a custom game engine, back to my origins!

### Setting Sail

There are 120k+ lines on the unity ecs codebase, so it will take some time for modules to be ported.

So far 12,031 lines have been written, with a great deal of macros to decrease the overall line count.

## Screenshots

Zoxel (C, FLECS, SDL)

![Zoxel](/documents/screenshots/screenshot-67e5703e.jpg?raw=false "Zoxel")

Old Zoxel (C#, Unity ECS)

![Unity Zoxel](/documents/screenshots/KEyHna.png?raw=false "Old Zoxel")

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