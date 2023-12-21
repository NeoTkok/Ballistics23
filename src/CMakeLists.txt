file(GLOB_RECURSE SOURCES *.hpp *.cpp)

add_library(${PROJECT_NAME} STATIC ${SOURCES})

set(TARGET_LIBRS eigen3 sofa)

target_include_directories(${PROJECT_NAME} PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})

target_link_libraries(${PROJECT_NAME} PUBLIC ${TARGET_LIBRS})
