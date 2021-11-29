set(FETCHCONTENT_BASE_DIR ${CMAKE_BINARY_DIR}/glog)
# set(WITH_GFLAGS off)

FetchContent_Declare(
        Glog
        GIT_REPOSITORY https://github.com/google/glog.git
        CMAKE_ARGS -DBUILD_TESTING=OFF
)

FetchContent_MakeAvailable(Glog)
