set(CMAKE_CXX_FLAGS "-std=c++11")

include_directories("../src")
include_directories("../googletest/googletest/include")

find_library(GTEST
    NAMES "gtest"
    PATHS ${PROJECT_SOURCE_DIR}/googletest/googletest/build
    NO_DEFAULT_PATH
)

add_executable(test
    test.cpp
)

target_link_libraries(test ${GTEST} pthread)