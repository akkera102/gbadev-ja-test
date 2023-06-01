# DeflemaskGBVGMConverter
Converts a Deflemask genrated .vgm in to .bin files containing bank separated custom register dump.

# Build Instructions
ensure that if the ASM rom has been updated:
- you use rom2CArr.py to generate a new ROM char array for the C converter then update `patchrom.h`
- you run generateRomPointers.py and check that the `Deflemask Player ROM Pointers` constant defines have not been changed. If so then update them.
## Windows
run minGW make.
## Linux
not yet supported
