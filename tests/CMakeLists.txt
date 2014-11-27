enable_testing()


# include Catch test framework
include_directories(catch/include)
include_directories(..)

add_executable(run_tests test_main.cpp)
target_link_libraries(run_tests iso226)

add_test(NAME "ISO226 test" COMMAND $CMAKE_CURRENT_BINARY_DIR/run_tests
         WORKING_DIRECTORY $CMAKE_CURRENT_BINARY_DIR)

