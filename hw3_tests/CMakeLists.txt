cmake_minimum_required(VERSION 3.4)

set(HW_NUMBER 3)
set(IS_CHECKER TRUE)

message("########################################################")
message("                 CS104 HW${HW_NUMBER} Test Suite")
message("########################################################")

project(CS104-HW${HW_NUMBER}-Test-Suite C CXX)

# Tell the compiler where to find headers like random_generator.h in testing_utils
include_directories(${CMAKE_SOURCE_DIR}/testing_utils)

# pick up additional CMake modules
list(APPEND CMAKE_MODULE_PATH ${CMAKE_SOURCE_DIR}/test_cmake_lib)
include(Policies NO_POLICY_SCOPE)
include(Utils)
include(Shorthand)
include(LibraryUtils)
include(104CompileFlags)
include(TestTargets)

# setup Valgrind
find_program(VALGRIND NAMES valgrind DOC "Path to valgrind executable")
import_executable(valgrind ${VALGRIND})
set(VALGRIND_ARGS --tool=memcheck --leak-check=yes --trace-children=no)
if(IS_CHECKER)
  list(APPEND VALGRIND_ARGS --error-exitcode=113)
endif()

# find GTest and Threads
find_package(GTest REQUIRED)
find_package(Threads REQUIRED)
import_libraries(gtest LIBRARIES ${GTEST_LIBRARIES} Threads::Threads INCLUDES ${GTEST_INCLUDE_DIRS})
import_libraries(gtest_main LIBRARIES ${GTEST_MAIN_LIBRARIES} INCLUDES ${GTEST_INCLUDE_DIRS})
include(CustomTests)
enable_testing()

# find user code directory (HW_DIR)
if(NOT DEFINED HW_DIR)
  file(GLOB PARENT_DIR_CPP_FILES "${CMAKE_BINARY_DIR}/../*.h" "${CMAKE_BINARY_DIR}/../*.cpp")
  if("${PARENT_DIR_CPP_FILES}" STREQUAL "")
    message(FATAL_ERROR "Cannot find source files in parent directory. Either move this test directory to your hw${HW_NUMBER} dir, or run CMake with -DHW_DIR=<path to hw${HW_NUMBER}>")
  else()
    get_filename_component(PARENT_DIR_REALPATH "${CMAKE_BINARY_DIR}/.." REALPATH)
    message(STATUS "HW_DIR autoset to ${PARENT_DIR_REALPATH}")
    set(HW_DIR ${PARENT_DIR_REALPATH} CACHE PATH "Path to hw${HW_NUMBER} assignment directory")
  endif()
endif()
get_filename_component(HW_DIR "${HW_DIR}" REALPATH)

# Build the testing utilities library.
add_subdirectory(testing_utils)

# Build the test suites.
add_subdirectory(llrec_tests)
add_subdirectory(stack_tests)
add_subdirectory(heap_tests)
if(NOT IS_CHECKER)
  gen_grade_target()
endif()

# --- Logic Simulator Setup ---

# Create a library for your circuit simulation code.
# (The source files are located in the logicsim folder in HW_DIR)
add_library(hw3_circuit
    ${HW_DIR}/logicsim/circuit.cpp
    ${HW_DIR}/logicsim/gate.cpp
    ${HW_DIR}/logicsim/wire.cpp
)

# Define the logicsim executable (your simulation main).
add_executable(logicsim
    ${HW_DIR}/logicsim/logicsim.cpp
)

# Link logicsim with the circuit library and other needed libraries.
target_link_libraries(logicsim
    hw3_circuit
    testing_utils
    Threads::Threads
)
