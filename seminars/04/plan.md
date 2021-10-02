[video](https://www.youtube.com/watch?v=_Ivd3qzgT7U)

1. Catch order matters (order_matters.cpp)
2. Stack unwinding
  * combining new-delete and exceptions is a bad idea. (new_and_unwinding.cpp)
  * destructors and more new-delete (destructors_and_catch.cpp)
  * throw exceptions and try to catch them in the same try-catch block (rethrow_multi_catch.cpp)
  * destructors order (stack unwinding) (long_exception.cpp)

3. noexcept
  * noexcept (move_noexcept.cpp)
  * move_if_noexcept
  * throw with noexcept (lier.cpp)
  * noexcept(std::is_pod<T>)

4. Exception safety
* Nothrow exception guarantee, e.g. destructor (bad_destructor.cpp)
* Strong exception guarantee --- state just before the function call (on exception), e.g. vector::push_back
* Basic exception guarantee --- valid state (throw_constructor.cpp)
5. Performance (performance.cpp)
```
perf 0  0.18s user 0.00s system 98% cpu 0.183 total
perf 1  15.58s user 0.00s system 99% cpu 15.587 total
```

6. Throw by value, catch by reference (catch_reference_of_value.cpp)
