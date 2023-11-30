cmake_minimum_required(VERSION 3.26.4)
project(Ballistics23)

set(CMAKE_CXX_STANDARD 20)


add_subdirectory(third_party)

add_subdirectory(src)

if(WITH_TESTS_INITIAL_ORBIT_DETERMINATION)
    add_subdirectory(tests)
endif()