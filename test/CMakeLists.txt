cmake_minimum_required(VERSION 3.12.4)

project(Tests)

add_subdirectory(${CMAKE_SOURCE_DIR}/test/google_test)
add_executable(OptionalTasks ${CMAKE_SOURCE_DIR}/test/OptionalTasks.cpp)

set_target_properties(OptionalTasks
        PROPERTIES
        CXX_STANDARD 17
        CXX_STANDARD_REQUIRED ON
        )
target_include_directories(OptionalTasks PRIVATE ${CMAKE_SOURCE_DIR}/google_test ${CMAKE_SOURCE_DIR}/src)
target_link_libraries(OptionalTasks PRIVATE gtest gtest_main)

add_test(NAME OptionalTasks COMMAND OptionalTasks)