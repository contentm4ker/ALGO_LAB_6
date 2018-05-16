add_executable(ps ${SOURCE1_EXE})
target_link_libraries(ps aho_corasick)
add_executable(joker ${SOURCE2_EXE})
target_link_libraries(joker aho_corasick wc_func)