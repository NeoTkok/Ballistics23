file(GLOB_RECURSE SOURCES *.h *.c)

add_library(sofa STATIC ${SOURCES})

target_include_directories(sofa PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})