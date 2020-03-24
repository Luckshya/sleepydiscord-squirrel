add_library(discord04rel SHARED
	CallbackHandler.cpp
	CallbackHandler.h
   	CDiscord.cpp
	CDiscord.h
	CSession.cpp
	CSession.h
	CMessage.cpp
	CMessage.h
	DEmbed.cpp
	DEmbed.h
	Functions.cpp
	Functions.h
	main.cpp
	main.h
	SQFunctions.cpp
)

if(BUILD_64)
	target_compile_options(discord04rel PRIVATE -D_SQ64)
endif()

target_include_directories(discord04rel
	PRIVATE
		${PROJECT_SOURCE_DIR}/src
		${PROJECT_SOURCE_DIR}/include
)

target_link_libraries(discord04rel sleepy-discord)