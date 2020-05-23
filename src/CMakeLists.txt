add_library(SqDiscord SHARED
		CallbackHandler.cpp
		CallbackHandler.h
		CDiscord.cpp
		CDiscord.h
		CSession.cpp
		CSession.h
		CError.h
		CMessage.h
		DEmbed.cpp
		DEmbed.h
		Functions.cpp
		Functions.h
		main.cpp
		main.h
		SQFunctions.cpp
		)

# Force 32-bit binaries when necessary
if(FORCE_32BIT_BIN)
	set_target_properties(SqDiscord PROPERTIES COMPILE_FLAGS "-m32" LINK_FLAGS "-m32")
	message("FORCING 32 BIT BINARIES")
endif()

# Size of a pointer in bytes. To identify CPU architecture.
if(CMAKE_SIZEOF_VOID_P EQUAL 8)
	target_compile_definitions(SqDiscord PRIVATE _SQ64)
	message("DEFAULTING TO 64 BIT BINARIES")
endif()

# Don't prefix the module binary.
set_target_properties(SqDiscord PROPERTIES PREFIX "")

# Custmize module binary name/
if(WIN32)
	if(CMAKE_SIZEOF_VOID_P EQUAL 8 AND NOT FORCE_32BIT_BIN)
		set_target_properties(SqDiscord PROPERTIES OUTPUT_NAME "discord04rel64")
	else()
		set_target_properties(SqDiscord PROPERTIES OUTPUT_NAME "discord04rel32")
	endif()
else(WIN32)
	if(CMAKE_SIZEOF_VOID_P EQUAL 8 AND NOT FORCE_32BIT_BIN)
		set_target_properties(SqDiscord PROPERTIES OUTPUT_NAME "discord04rel64")
	else()
		set_target_properties(SqDiscord PROPERTIES OUTPUT_NAME "discord04rel32")
	endif()
endif(WIN32)

target_include_directories(SqDiscord
	PRIVATE
		${PROJECT_SOURCE_DIR}/src
		${PROJECT_SOURCE_DIR}/include
)

target_link_libraries(SqDiscord sleepy-discord)