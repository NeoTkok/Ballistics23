add_subdirectory(sofa)
add_subdirectory(googletest)

add_library(eigen3 INTERFACE)

target_include_directories(eigen3 INTERFACE eigen)