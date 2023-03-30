# SCPI Parser port to Arduino
SCPI Parser for advanced programmers or instrumentation engineers. Not suitable for beginners to Arduino. For a lighter-weight solution in your Arduino projects, consider the [Vrekrer SCPI Parser library](https://github.com/Vrekrer/Vrekrer_scpi_parser). It is much simpler and easier to incorporate into your Arduino code.

This repository holds an Arduino port of the [SCPI Parser library](https://github.com/j123b567/scpi-parser) (which is C/C++ code). The SCPI Parser library is an open project written by Jan Breuer.

This port is not tested on any boards except for the Teensy 4.1. It does not work on the Arduino Uno, Arduino Nano, etc.

## Authorship
The SCPI Parser C/C++ library is **not** written by me. I ported it to Arduino so we could use this powerful library easily with Teensy 4.1 boards, which use the Arduino IDE, to develop embedded devices that communicate over SCPI.

The SCPI Parser C/C++ library is written by **Jan Breuer** and is contributed to by a variety of community members. The source code for SCPI Parser (C/C++) is hosted at https://github.com/j123b567/scpi-parser. The documentation is hosted at http://j123b567.github.io/scpi-parser.

## Installing the library
This library is meant to be installed through the Arduino library manager. You can also download it manually into your Arduino libraries folder.

## References I used while porting this library to Arduino

1. [Arduino Libraries](https://docs.arduino.cc/hacking/software/Libraries)
1. [Building a Library for Arduino](https://docs.arduino.cc/learn/contributions/arduino-creating-library-guide)
1. [Library Specification](https://arduino.github.io/arduino-cli/0.31/library-specification/)

## Steps I took to port this library to Arduino
Created a new folder.

Inside that folder, created library.keywords file and filled it with content.
```
name=SCPI-Parser
version=2.2.0
author=Jan Breuer
maintainer=Scott Feister
sentence=Port of SCPI Parser library (C/C++) to Arduino. Aims to provide parsing ability of SCPI commands on instrument side.
paragraph=SCPI parser library is based on these standards: SCPI-99, IEEE 488.2-2004. This Arduino port was made by downloading SCPI Parser's most recent GitHub version as of March 4, 2023, so that recent C++ fixes were included. SCPI Parser (C/C++) git version was 4e87990. This is therefore not actually version 2.2.0, but slightly ahead of that version.
category=Device Control
url=https://www.jaybee.cz/scpi-parser/
includes=scpi.h
architectures=*
```

Create a folder called "SCPI-Parser".

Create a new folder named "src". This will store all source code and headers. (See Library Specification reference for Arduino, above).

1. From the SCPI Parser GitHub page, copy over the "root/libscpi/src" folder in its entirety. This becomes "/src/src" in the Arduino Library.
1. From the SCPI Parser GitHub page, copy over the "root/libscpi/inc/scpi" folder in its entirety. This becomes "/src/scpi" in the Arduino Library.
1. Within the Arduino Library, move the file "/src/scpi/scpi.h" up one level so it becomes "/src/scpi.h".

## Included Example
This Arduino library contains just one example. This example is a direct port of the "test-interactive" example from the "examples" folder of the original source code of SCPI Parser.

The following files were adapted from the original source code of SCPI Parser while porting this example:
* root/examples/common-cxx/scpi-def.cpp
* root/examples/common-cxx/scpi-def.h
* root/examples/test-interactive-cxx/main.cpp

In particular, for scpi-def.cpp and scpi-def.h, I just replaced `include "scpi/scpi.h"` with `include <scpi.h>.

The "test-interactive/main.cpp" required much more heavy modfication, and became "test-interactive.ino". You can interact with this test device through the Serial monitor of the Arduino IDE.

