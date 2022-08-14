#pragma once

struct Info {
    int copy = 0;
    int move = 0;
    bool rvalue = false;
};

struct Counted {
    Info info;

    Counted() = default;

    Counted(const Counted& other) {
        info.copy = other.info.copy + 1;
        info.move = other.info.move;
    }

    Counted(Counted&& other) {
        info.copy = other.info.copy;
        info.move = other.info.move + 1;
    }

    Info operator()(int) && {
        info.rvalue = true;
        return info;
    }

    Info operator()(int) const& {
        return info;
    }
};

constexpr Info Id(Info x) {
    return x;
}
