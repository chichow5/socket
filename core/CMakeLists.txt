
set(ALL_PLATFORM_FILE
    bridge.cpp
    bridge.h
    CMakeLists.txt
    debug.cpp
    debug.h
    networkpacket.cpp
    networkpacket.h
    transferstuff.cpp
    transferstuff.h)

set(IGNORE_FILE
    fakedaemon.cpp
    fakedaemon.h)

if (WIN32)
    add_library(corefun
        ${ALL_PLATFORM_FILE}
        winbasic.cpp
        winbasic.h)
elseif(UNIX)
    add_library(corefun
        ${ALL_PLATFORM_FILE}
        basic.cpp
        basic.h)
endif ()
