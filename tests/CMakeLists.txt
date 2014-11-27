# include Catch test framework
include_directories(catch/include)
include_directories(..)

add_executable(run_tests test_main.cpp)
target_link_libraries(run_tests iso226)

configure_file(plot.sh ${CMAKE_CURRENT_BINARY_DIR}/plot.sh)

add_test("Gnuplot" "sh" "${CMAKE_CURRENT_BINARY_DIR}/plot.sh")
add_test("ISO226" run_tests)

add_subdirectory(regression)

