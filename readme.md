![zoxel banner](https://pbs.twimg.com/media/GvGarlgbAAA3jG-?format=jpg&name=small)

### What is Zoxel?

* A procedural simulation role-playing game
* Inspired by Warcraft, Minecraft and Cube World
* Flat module structure, built with Flecs chaos
* Open‑source GPL license
* Voxels, stats, items, skills, quests, dialogue & more
* Experience the thrill of discovery & adventure!

---

### Requirements

- **Build tools:**  
  - `git`  
  - `make`  
  - `gcc` (or compatible C compiler)  

- **Libraries:**  
  - math (`-lm`)  
  - pthreads (`-lpthread`)  
  - Flecs ECS (`-lflecs`)  
  - SDL2 core (`-lSDL2`)  
  - SDL2 image support (`-lSDL2_image`)  
  - SDL2 mixer (audio) (`-lSDL2_mixer`)  
  - OpenGL (`-lGL`)

---

### Installing Dependencies

- **Debian / Ubuntu**

```bash
sudo apt install git gcc make libc6-dev libsdl2-dev libsdl2-image-dev libsdl2-mixer-dev libglew-dev
```

- **Arch Linux / Manjaro**

```bash
sudo pacman -S git gcc make glibc sdl2 sdl2_image sdl2_mixer glew
```

- **Alpine Linux**

```bash
sudo apk add git gcc make ibc-dev sdl2-dev sdl2_image-dev sdl2_mixer-dev glew-dev
```

---

### How do I Build?

```bash
git clone https://codeberg.org/deus/zoxel
cd zoxel
mkdir build
mkdir build/zoxel-linux
cp -R resources build/zoxel-linux/resources
make
make run
```

---

### The Docs

The ultimate plan - [ todo list ](todo.md)

Building is on - [zoxelder](https://codeberg.org/deus/zoxelder)

Flecs requires 3.2.7 - [flecsing](https://codeberg.org/deus/flecsing)

---

### The Socials

  - [ twitter ](https://twitter.com/deusxyz)
  - [ mastodon ](https://mastodon.gamedev.place/@deus)
  - [ itchio ](https://deusxyz.itch.io/zoxel-foss)
  - [ youtube ](https://www.youtube.com/watch?v=Hseq5iPIJ6s)
  - [ codeberg ](https://codeberg.org/deus/zoxel)
  - [_github_](https://github.com/deus369/zoxel)
