set(CMAKE_CXX_FLAGS "-Wall -std=c++11")

enable_testing()

include_directories("../src")
include_directories("../googletest/googletest/include")

find_library(GTEST
    NAMES "gtest"
    PATHS ${PROJECT_SOURCE_DIR}/googletest/googletest/build
    NO_DEFAULT_PATH
)

add_executable(test1 test1.cpp)
add_executable(test2 test2.cpp)

target_link_libraries(test1 ${GTEST} pthread)
target_link_libraries(test2 ${GTEST} pthread)

add_test(NAME test1 COMMAND test1)
add_test(NAME test2 COMMAND test2)

add_custom_command(
  OUTPUT _test1_completed
  COMMAND ./test1
  DEPENDS test1
)

add_custom_command(
  OUTPUT _test2_completed
  COMMAND ./test2
  DEPENDS test2
)

add_custom_target(
  test1_force ALL
  DEPENDS _test1_completed
)

add_custom_target(
  test2_force ALL
  DEPENDS _test2_completed
)