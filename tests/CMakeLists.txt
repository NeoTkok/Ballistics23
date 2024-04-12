include_directories(
        ${gtest_SOURCE_DIR}/include
        ${gtest_SOURCE_DIR}
        ${PROJECT_SOURCE_DIR}/src/ballistics
        ${PROJECT_SOURCE_DIR}/data
)

file(GLOB_RECURSE TEST_SOURCES test_*.cpp)
foreach (test ${TEST_SOURCES})
    get_filename_component(TEST_FILE_NAME ${test} NAME_WLE)
    set(EXECUTABLE_NAME run_${TEST_FILE_NAME})

    message("GOOOD")
    add_executable("${EXECUTABLE_NAME}" ${test})
    add_test(NAME "${EXECUTABLE_NAME}" COMMAND ${test})
    target_link_libraries("${EXECUTABLE_NAME}" ${PROJECT_NAME} gtest gtest_main)
endforeach ()


