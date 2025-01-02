# TODO list

## UI

- Maybe make alignments after all?

## Build script

CMake+Make are not enough, I have to add an asset cooking step now, which will create an archive of all data that is used in the game.

- Make a C++ program (I'd rather not do bash scripts for this type of thing) that will optionally (if necessary or explicitly specified) generate the game asset archive.
- It should optionally redo cmake.
- It should run make with 16 processes.

## Asset manager

- GameContext singleton (which holds AssetManager, SoundManager, maybe even NetworkManager)
- File Archive or something, a class that will represent the loaded archive

## Asset editor (tentative)

- Consider making an asset editor so that sprites can be easier created visually and interactively.
