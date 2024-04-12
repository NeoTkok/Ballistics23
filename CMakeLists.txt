cmake_minimum_required(VERSION 3.26.4)
project(Ballistics23)

set(CMAKE_CXX_STANDARD 20)

add_subdirectory(src)
add_subdirectory(third_party)


if (WITH_TESTS)
    add_subdirectory(tests)
endif ()

