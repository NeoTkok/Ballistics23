#file(GLOB_RECURSE SOURCES sofa/*.h sofa/*.c)
#
#add_library(sofa STATIC ${SOURCES})
#
#target_include_directories(sofa PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})

add_subdirectory(sofa)

add_subdirectory(googletest)

add_library(eigen3 INTERFACE)

target_include_directories(eigen3 INTERFACE eigen)