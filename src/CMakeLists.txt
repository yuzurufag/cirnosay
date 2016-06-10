find_package(PkgConfig REQUIRED)
pkg_check_modules(IMLIB2 imlib2 REQUIRED)
link_directories(${IMLIB2_LIBRARY_DIRS})
include_directories(${IMLIB2_INCLUDE_DIRS})
link_libraries(${IMLIB2_LIBRARIES})

add_definitions(-std=c++0x -O3 -Wall -Wextra)

add_executable (cirnosay 
	canvas/border_simple.cpp
	canvas/compose.cpp
	canvas/picture.cpp
	canvas/text.cpp
	char.cpp
	cirnosay.cpp
	color.cpp
	findfile.cpp
	out.cpp
	palette.cpp
	picture.cpp
	rgba.cpp
	utils.cpp
	)

configure_file(config.h.in config.h ESCAPE_QUOTES)

install(TARGETS cirnosay RUNTIME DESTINATION bin)
