# CHIP-8-Emulator
A CHIP-8 interpreter emulator written in C.
Followed high level tutorials and referenced data sheets to come up with my implementation.
Using SDL for the graphics and key inputs.

## Installation
You must have SDL2 and gcc installed to compile the files with the makefile.

## Usage
- Run the makefile to create the executable file.
- Place a CHIP-8 ROM in the ROM directory.
- Enter ```chip8 filename``` in the shell.

## TODO
- Cap FPS to 60 and tie timers to it to get reasonable game speeds
- Implement beep sound
- ROM selection interface
