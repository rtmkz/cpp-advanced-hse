add_catch(test_grep test.cpp)
set_property(TARGET test_grep PROPERTY CXX_STANDARD 17)
target_link_libraries(test_grep stdc++fs)