message(STATUS "Found LLVM ${LLVM_PACKAGE_VERSION}")
message(STATUS "Using LLVMConfig.cmake in: ${LLVM_DIR}")
message(STATUS "LLVM include dir is ${LLVM_INCLUDE_DIR}")

set(SRC check_names.cpp)
include_directories(.)

include_directories(${LLVM_INCLUDE_DIRS})
add_definitions(${LLVM_DEFINITIONS})
link_directories(${LLVM_LIBRARY_DIRS})

# include_directories(${LLVM_BUILD_MAIN_SRC_DIR}/tools/clang/include)
# include_directories(${LLVM_BUILD_BINARY_DIR}/tools/clang/include)
# include_directories(${LLVM_BUILD_BINARY_DIR}/lib/clang/5.0.0/include)

add_executable(check-names ${SRC})
set_target_properties(check-names PROPERTIES COMPILE_FLAGS "-Wno-unused-parameter -Wno-unused-variable -fno-rtti")

llvm_map_components_to_libnames(llvm_libs all)
set(clang_libs clangFrontend clangSerialization clangDriver)

if (${LLVM_PACKAGE_VERSION} VERSION_EQUAL 7 OR ${LLVM_PACKAGE_VERSION} VERSION_GREATER 7)
  list(APPEND clang_libs clangASTMatchers)
endif()

list(APPEND clang_libs clangParse clangSema clangCodeGen clangAnalysis clangRewrite clangEdit
     clangAST clangLex clangTooling clangBasic)
target_link_libraries(check-names ${llvm_libs} ${clang_libs} LLVM-11)

set(TESTS_LIST
    tests/no-dict/fun.cpp
    tests/no-dict/perm.cpp
    tests/no-dict/segment.cpp
    tests/dict/test_file.cpp
    tests/dict/sorting.cpp
)

foreach (test ${TESTS_LIST})
    get_filename_component(result ${test} NAME_WE)
    add_executable("clang_test_${result}" ${test})
endforeach(test)
