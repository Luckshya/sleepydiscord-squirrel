add_library(SqDiscord SHARED
        EventHandler.h
        Common.hpp
        Common.cpp
        Constants.h
        Constants.cpp
        CDiscord.cpp
        CDiscord.h
        CSession.cpp
        CSession.h
        DEmbed.cpp
        DEmbed.h
        main.cpp
        main.h
        SQFunctions.cpp
        Guild.cpp
        Guild.h
        Role.cpp
        Role.h
        ServerMember.cpp
        ServerMember.h
        Channel.cpp
        Channel.h
        User.cpp
        User.h
        Message.cpp
        Message.h)

# Force 32-bit binaries when necessary
if (FORCE_32BIT_BIN)
    set_target_properties(SqDiscord PROPERTIES COMPILE_FLAGS "-m32" LINK_FLAGS "-m32")
    message("FORCING 32 BIT BINARIES")
endif ()

# Size of a pointer in bytes. To identify CPU architecture.
if (CMAKE_SIZEOF_VOID_P EQUAL 8)
    target_compile_definitions(SqDiscord PRIVATE _SQ64)
    message("DEFAULTING TO 64 BIT BINARIES")
endif ()

# Don't prefix the module binary.
set_target_properties(SqDiscord PROPERTIES PREFIX "")

# Custmize module binary name/
if (WIN32)
    if (CMAKE_SIZEOF_VOID_P EQUAL 8 AND NOT FORCE_32BIT_BIN)
        set_target_properties(SqDiscord PROPERTIES OUTPUT_NAME "discord04rel64")
    else ()
        set_target_properties(SqDiscord PROPERTIES OUTPUT_NAME "discord04rel32")
    endif ()
else (WIN32)
    if (CMAKE_SIZEOF_VOID_P EQUAL 8 AND NOT FORCE_32BIT_BIN)
        set_target_properties(SqDiscord PROPERTIES OUTPUT_NAME "discord04rel64")
    else ()
        set_target_properties(SqDiscord PROPERTIES OUTPUT_NAME "discord04rel32")
    endif ()
endif (WIN32)

target_include_directories(SqDiscord
        PRIVATE
        ${CMAKE_SOURCE_DIR}/src
        ${CMAKE_SOURCE_DIR}/include
        ${CMAKE_SOURCE_DIR}/readerwriterqueue
        )

target_link_libraries(SqDiscord sleepy-discord)