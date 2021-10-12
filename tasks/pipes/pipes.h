#pragma once

#include <utility>

/// You can use template arguments if you want
struct pipe_line {
    constexpr auto operator|(auto f) const {
        return {};  /// 1
    }

    template <class Arg>
    constexpr auto operator()(Arg&& arg) const {
        return {};  /// 2
    }
};

struct empty_pl_helper {
    constexpr auto operator|(auto f) const {
        return pipe_line();  /// 3
    }
};

constexpr auto empty_pl{empty_pl_helper()};
