include_directories(${gtest_SOURCE_DIR}/include ${gtest_SOURCE_DIR})

file(GLOB_RECURSE TEST_SOURCES test_*.cpp)
set(LIBS ${PROJECT_NAME}  gtest gtest_main)

foreach (TEST_FILE IN LISTS TEST_SOURCES)
    get_filename_component(TEST_FILE_NAME ${TEST_FILE} NAME_WE)
    set(EXECUTABLE_NAME run_${TEST_FILE_NAME})
    add_executable(${EXECUTABLE_NAME} ${TEST_FILE})

    target_link_libraries(${EXECUTABLE_NAME} ${LIBS})

    add_test(NAME ${EXECUTABLE_NAME} COMMAND ${EXECUTABLE_NAME})
endforeach ()