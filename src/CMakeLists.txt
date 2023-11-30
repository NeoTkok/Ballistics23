file(GLOB_RECURSE SOURCE *.hpp *.cpp)

add_library(${PROJECT_NAME} STATIC ${SOURCES})
set(TARGET_LIBRS eigen3 sofa gtest gtest_main)
target_link_libraries(${PROJECT_NAME} PUBLIC ${TARGET_LIBRS})

target_include_directories(${PROJECT_NAME} PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})