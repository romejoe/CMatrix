#What to include
##Options
### ByteStream.h
This header contains the structure definition and function prototypes. Keep in mind that you must also compile ByteStream.c.
### FullByteStream.h
This header contains ByteStream.h and the implementation code. This allows you to include 1 file and not modify your build at all. Note that this file can only be included once per executable. Including it more than once will cause some(perhaps all) compilers to fail at the linking stage. In those cases, include FullByteStream.h in one file, then include ByteStream.h everywhere else.