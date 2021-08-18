#include <iostream>
#include <vector>

struct MoveOnly {
  MoveOnly() = default;
  MoveOnly(const MoveOnly&) = delete;
  MoveOnly& operator=(const MoveOnly&) = delete;
//  MoveOnly(MoveOnly&&) = default;  // default actually implies noexcept
//  MoveOnly& operator=(MoveOnly&&) = default;
};

int main() {
  std::vector<MoveOnly> kek(2);
  kek.emplace_back();  // doesn't compile without move-constructor being marked noexcept!
  // static_assert(std::is_nothrow_move_constructible_v<MoveOnly>);

  // Why?
  // If the move-constructor throws, reallocation would violate strong exceptions safety guarantees:
  // an exception in the midst of reallocating can leave some old elements in a moved-from
  // state, and it is not possible to move them back, since that could also throw.
  // If we are copying, we can simply destroy the newly created copies, as the originals were
  // kept intact.
}
