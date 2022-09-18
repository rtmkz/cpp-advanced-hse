# ------------------------------------------------------------------------------
# UniquePtr

add_catch(test_unique unique/test.cpp)

# ------------------------------------------------------------------------------
# SharedPtr + WeakPtr

add_catch(test_shared_basic shared-basic/test.cpp)
add_catch(test_shared_weak shared-basic/test.cpp shared-weak/test.cpp)
add_catch(test_shared_from_this shared-basic/test.cpp shared-weak/test.cpp shared-from-this/test.cpp)

target_link_libraries(test_shared_basic allocations_checker)
target_link_libraries(test_shared_weak allocations_checker)
target_link_libraries(test_shared_from_this allocations_checker)

# ------------------------------------------------------------------------------
# IntrusivePtr

add_catch(test_intrusive intrusive/test.cpp)
target_link_libraries(test_intrusive allocations_checker)
