file(GLOB_RECURSE SOURCES *.h *.cpp *.hpp *.c)

add_library(${PROJECT_NAME} STATIC ${SOURCES})

target_include_directories(${PROJECT_NAME} PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})

target_link_libraries(${PROJECT_NAME} PUBLIC sofa eigen GeographicLib_SHARED calceph)
