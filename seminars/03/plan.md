For group 3:

- EBO with template specializations
- Why types of size 0 are not allowed
- SSO in depth
- view containers (string_view, span) and their cost
- static variables, SIOF, cin & cout
- constexpr variables

Lambdas:

- Lambdas: why are they needed in C++
- Decay to pointer-to-function
- Capture list: capturing by value, reference, rvalue reference
- Capture list: capturing this, this-by-copy
- Capture list: renamed args, args with default values, variadic capture, capture with functor application.
- Lambdas in code: cppinsights -- unnamed functor with unique type
- Mutable lambdas
- Template lambdas (and their operator())
- Recursive lambdas
- decltype(lambda_type) for STL containers.
- [optional] Abbreviated lambdas proposal -- why and what for

Smart pointers -- unique:

- Unique without deleter overview: pointer to object with RAII
- What is different for T[]?
- How should we handle exceptions? Remember make-unique and unspecified order of func args evaluation
- Move/copy/swap semantics for unique
- Corner cases for a = a, a = move(a) etc.
- Polymorphic instantiation, unique<Base> = new Derived.
- Dereference and its invariants, checking for value
- Deleter: how to use, where to store.
- Deleter for arrays.
- Polymorphic deleters.

Smart pointers -- shared & weak

- Shared without a deleter: pointer + atomic
- Move/copy semantics on underlying atomic
- Deleters: why should we create a control block. How many allocations we get (without make-shared)
- Remind: why shared-from-this is needed
- Remind: cyclic dependencies with shared, solution -- weak
- optional<> semantics for weak ptr.
- weak-from-this
