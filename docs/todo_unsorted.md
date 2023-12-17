## io

- [x] load vox dynamically
- [x] load sounds dynamically
- [ ] load generic textures, linking to realm
    - [ ] load textures dynamically from textures folder in resources
    - [ ] draw a texture inside a test element - link it there
- [ ] save file in multithread
- [ ] push save file to steam cloud when saving

## game

- [x] user stat to share data with meta data of stat
    - [ ] meta data have name, description, TextureLink
    - [ ] test deletion to make sure only meta data deletes texture

- [ ] link user skill to a texture
- [ ] link actionbar ui to character
- [ ] spawn player character user action entities
- [ ] spawn player character user skill entities

## ui

- [x] fix editor issue where hierarchy and inspector spawn but children fails
- [x] inspector - update list dynamically with scroll
- [ ] window  sorting by last clicked one (make a window stack)
- [ ] input field ui on terminal window
- inspector
    - [ ] if entity dies, perhaps remove selection off inspector
    - [ ] set position of labels to left of the ui in the list, left anchoring
        - [ ] tab out based on a 'tab' character
    - [ ] add float3, float4, entity, doubles (deadtime) and anything else i can too editor values
    - [ ] don't delete old children just reuse for list updates


## web build

- [x] Fix terrain rendering not showing visually, opengl errors?
- [ ] Fix EM_JS functions not working anymore (platforms/util/webasm_util.c)
- [ ] Fix Pipeline, 'make push-web' should push to a zox-web git repo the latest build
    - test with zoxel-web

## devops

- [ ] automate beta builds every saturday it should perform all platforms
- [ ] test results can be displayed in a simple text file
- [ ] push builds to git repo every week on a saturday

=================================
    builds started at [3.18PM - 11/23/23]
=================================
    linux x86_64 [passed]
    linux x86_32 [passed]
    windows x86_64 [passed]
    windows x86_32 [passed]
    webasm [passed]
    android [failed]
    linux arm64 [passed]
=================================
    builds completed at [6.18PM - 11/23/23]
=================================

## cross compile to windows

- [x] get a 'make build/zoxel.exe' build working

## steamdeck steam

- [x] install_sdk for steamworks
- [x] add steamworks to zoxel compilation with a toggle option
- [x] 'make is_steamworks' check if steamworks is in build
- [x] test achievement for killing first npc - [noob] Vox Slayer! You have started your journey into the path of carnage.

