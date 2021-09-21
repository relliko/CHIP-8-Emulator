# :space_invader: CHIP-8 Emulator :space_invader:
![Space Invaders Title Screen](https://github.com/relliko/CHIP-8-Emulator/blob/master/preview.png)
A CHIP-8 interpreter emulator written in C.
Followed high level tutorials and referenced data sheets to come up with this implementation.
Using SDL2 for the graphics and key inputs.

## Installation
You must have SDL2 and GCC installed to compile the files with the makefile.
```sudo apt-get install libsdl2-dev```

## Usage
- Run the makefile to create the executable file.
- Place a CHIP-8 ROM in the ROM directory.
- Enter ```./chip8 filename``` in the shell.

Controls:  
1234  
qwer  
asdf  
zxcv  


## TODO
- Make game speed configurable to be compatible with a wider variety of games.
- Implement beep sound
- Maybe compile it to WebAssembly
