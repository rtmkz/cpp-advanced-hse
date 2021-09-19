For group 3:

- EBO with template specializations
- Why types of size 0 are not allowed
- SSO in depth
- view containers (string_view, span) and their cost
- static variables, SIOF, cin & cout
- constexpr variables

Templates:

- Why and what for
- typename and template -- why and what for (parsing ambiguity)
- traits in STL (aliases, constexpr variables). SFINAE basics.
- Partial spec for structs. Spec for functions.
- Remind: forward declaration.
- Special case: templates in .cpp and template class.
- concepts
- [optional] Non-type template parameters

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
- Aliasing constructor: pointer to member object while keeping its parent alive
- Deleters: why should we create a control block. How many allocations we get (without make-shared). weak-count
- Remind: why shared-from-this is needed
- Remind: cyclic dependencies with shared, solution -- weak (control block + pointer).
- weak ptr and lock().
- optional<> semantics for weak ptr.
- weak-from-this

Lambdas (optional):

- Lambdas: why are they needed in C++
- Decay to pointer-to-function (operator +)
- IILE
- Capture list: capturing by value, reference, rvalue reference
- Capture list: capturing this, this-by-copy
- Capture list: renamed args, args with default values, variadic capture, capture with functor application.
- Lambdas in code: cppinsights -- unnamed functor with unique type
- Mutable lambdas
- Template lambdas (and their operator())
- Recursive lambdas
- decltype(lambda_type) for STL containers.
- Abbreviated lambdas proposal -- why and what for
