# BEBSDK
Crossplatform C++ SDK used in various projects created by me (Benoit BOUCHEZ)

Supported platforms :
- Windows
- Mac OS
- Linux

## Project shall define in preprocessor or makefile
- `#define __TARGET_LINUX__`    to compile the libraries under Linux
- `#define __TARGET_WIN__`      to compile the libraries under Windows
- `#define __TARGET_MAC__`      to compile the libraries under MacOS

IMPORTANT
- One and only one target must be defined !
- The define begins and end with a double underscore (in other terms : __ is 2x _)
