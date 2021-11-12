#pragma once

#include <utility>
#include <optional>

template <class T>
class BufferedChannel {
public:
    explicit BufferedChannel(int size) {
    }
    void Send(const T& value) {
    }
    std::optional<T> Recv() {
        return std::nullopt;
    }
    void Close() {
    }
};
