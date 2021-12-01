set(FETCHCONTENT_BASE_DIR ${CMAKE_BINARY_DIR}/glog)
set(WITH_GFLAGS off)
set(CMAKE_POLICY_DEFAULT_CMP0077 NEW)
option(BUILD_SHARED_LIBS "Build shared libraries" OFF)

add_compile_definitions(GLOG_CUSTOM_PREFIX_SUPPORT)

FetchContent_Declare(
        Glog
        GIT_REPOSITORY https://github.com/google/glog.git
        CMAKE_ARGS -DBUILD_TESTING=OFF
)

FetchContent_MakeAvailable(Glog)
