![zoxel banner](https://pbs.twimg.com/media/GvGarlgbAAA3jG-?format=png&name=large)

### What is Zoxel?

* A procedural simulation role-playing game
* Inspired by Warcraft, Minecraft and Cube World
* Flat module structure, built with Flecs chaos
* Open‑source GPL license
* Voxels, stats, items, skills, quests, dialogue & more
* Experience the thrill of discovery & adventure!

---

### How do I Build?

```bash
git clone --depth=1 https://codeberg.org/deus/zoxel
cd zoxel
make run
```

- Package it!

```bash
make package
```

---

### The Docs

The ultimate plan [ todo list ](todo.md)

Building is on [_zoxelder_](https://codeberg.org/deus/zoxelder)

Flecs (v3.2.7) [_flecsing_](https://codeberg.org/deus/flecsing)

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

### The Socials

  - [ twitter ](https://twitter.com/deusxyz)
  - [ mastodon ](https://mastodon.gamedev.place/@deus)
  - [ itchio ](https://deusxyz.itch.io/zoxel-foss)
  - [ youtube ](https://www.youtube.com/watch?v=Hseq5iPIJ6s)
  - [_github_](https://github.com/deus369/zoxel)
  - [ codeberg ](https://codeberg.org/deus/zoxel)

---

### Some Notes

 - Flecs 3.2.8, prefab tags dont check properly
 - Flecs 3.2.9 to 3.2.12 have crashes when exiting game
 - Need to refactor for 4, so have no tried yet