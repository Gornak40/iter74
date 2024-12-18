file(GLOB TEST_FILES test_*.c)

foreach(TEST_FILE ${TEST_FILES})
    get_filename_component(TEST_NAME ${TEST_FILE} NAME_WE)
    add_executable(${TEST_NAME} ${TEST_FILE} ${SRC_FILES})
    add_test(NAME ${TEST_NAME} COMMAND ${TEST_NAME})
endforeach()
