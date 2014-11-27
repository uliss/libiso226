configure_file(gen_regression_data.sh ${CMAKE_CURRENT_BINARY_DIR}/gen_regression_data.sh)
configure_file(test_regression.sh ${CMAKE_CURRENT_BINARY_DIR}/test_regression.sh)

add_test("regression" sh "${CMAKE_CURRENT_BINARY_DIR}/test_regression.sh")
