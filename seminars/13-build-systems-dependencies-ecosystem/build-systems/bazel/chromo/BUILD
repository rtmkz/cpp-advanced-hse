# Create library.
cc_library(
    name = "chromo",
    srcs = ["time.cpp"],
    hdrs = ["time.hpp"],
    visibility = [
        "//clocks:__pkg__",  # `chromo` is visible for all targets from `clocks`
        "//tests:__pkg__",   # `chromo` is visible tests, also
    ],
)
