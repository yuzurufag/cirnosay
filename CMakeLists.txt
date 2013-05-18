cmake_minimum_required (VERSION 2.6)
project (CIRNOSAY)

if(IN_PLACE)
	set(DATA_DIR ${CMAKE_SOURCE_DIR}/data)
else()
	set(DATA_DIR ${CMAKE_INSTALL_PREFIX}/share/cirnosay)
endif()

add_subdirectory(src)

install(DIRECTORY data/ DESTINATION ${DATA_DIR})
