add_source_problem(NAME llrec USER_SOURCE ${HW_DIR}/llrec.cpp TEST_SOURCE llrec_tests.cpp llrec_test_utils.cpp)

# Define llrec-test as an executable using both test sources.
add_executable(llrec-test
    llrec_tests.cpp
    llrec_test_utils.cpp
)

target_link_libraries(llrec-test
    hw3_llrec      # Your library built from llrec.cpp by add_source_problem
    gtest          # Link the Google Test library
    gtest_main     # Provides main() for running tests
    testing_utils  # If your project builds a testing_utils library
)
