project(dict_parser_test)

# add_executable(dict_parser_test_tmp dict_parser_tmp.cpp)
# target_link_libraries(dict_parser_test_tmp dict_parser)

add_executable(built_in_parser_test built_in_parser_test.cpp)
target_link_libraries(built_in_parser_test dict_parser gtest gtest_main pthread)  # link pthread to avoid linking error

add_executable(dict_parser_test dict_parser_test.cpp)
target_link_libraries(dict_parser_test dict_parser gtest gtest_main pthread)

enable_testing()
add_test(NAME built_in_parser_test
        WORKING_DIRECTORY ${CMAKE_CURRENT_BINARY_DIR}
        COMMAND ${CMAKE_CURRENT_BINARY_DIR}/built_in_parser_test)
add_test(NAME dict_parser_test
        WORKING_DIRECTORY ${CMAKE_CURRENT_BINARY_DIR}
        COMMAND ${CMAKE_CURRENT_BINARY_DIR}/dict_parser_test)

