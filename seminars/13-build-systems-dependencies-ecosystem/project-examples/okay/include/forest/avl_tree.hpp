#pragma once  // Can lead to problems that header guards prevent

#include "utils.hpp"  // Better to move `utils.hpp` to `forest/details/`

namespace forest {  // Good

template <typename T>  // Cannot specify custom allocator :(
class AVLTree {
public:
    // Implementation...

private:
    // Implementation...

    void ImplementationDetail() {
        DoImplementationDetail();
    }
};

}  // namespace forest
