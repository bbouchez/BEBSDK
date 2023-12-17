# BEBSDK
Crossplatform C++ SDK used in various projects created by me (Benoit BOUCHEZ)

Supported platforms :
- Windows
- Mac OS
- Linux

IMPORTANT : project shall define in preprocessor
- `#define __TARGET_LINUX__`    to compile the libraries under Linux
- `#define __TARGET_WIN__`      to compile the libraries under Windows
- `#define __TARGET_MAC__`      to compile the libraries under MacOS

One and only one target must be defined !
