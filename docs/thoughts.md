I need to do marching cubes for dirt
I need a good pipeline for models and animations - use realtime engine updates too for textures etc - if file_updates enabled
I should add text colors in terminal output
Terminal UI refresh per frame for server / headless modes - showing stats and log - take in inputs too
Generate voxels on gpu - because its cool
GPU Instancing of grass next - make a voxel have links to models and use one based on position in map and noise - maybe store a variation byte as well?
Give a new build folder - per <game_name>_<OS>_<architecture>
Make music good - import lmms files - use better piano notes for now until generation improves
Add auto tests in as parameters
Make a builder app?
Make editor app, it should reload modules of C code onto the game engine part
Make a damn start screen... what kind idk
Make a logo splash - penguin
Can we build parts of project at once instead of entire thing? .o files?
use 6 textures and generate inside of vox based on those, make sure edges line up too by picking randomly or merging colors to best fit
I need to make a no physics system where characters can just move around voxel position by position, use on outer chunks further from camera, or for different game modes

- networking -
run zoxel service on linode
clients will connect automatically
show an icon on main menu if connected
make a terminal in game that i can input messages to
send ping packets to server
server to show in realtime how many players connected

- ui -
the way to initialize the meshes is weird
cause we resize inside the canvas
perhaps we can just scale, have a canvas size and a scale still
so no need to recreate verts many times, just use static verts (theoritically can just use static entity ones instead of unique meshGPULink, use MeshGPULightLink to the initially uploaded ones)
