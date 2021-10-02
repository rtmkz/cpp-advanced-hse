contents = None

with open("schema.h", "r") as f:
    contents = f.readlines()

contents = contents[5:-1]

with open("reflection.h", "w") as out:
    print('#include "schema.h"\n', file=out)
    print("template <size_t I> constexpr auto& Get(Schema& schema);", file=out)

    for i, item in enumerate(contents):
        name = item.split()[-1][:-1]

        print(f"template <> constexpr auto&\
                Get<{i}>(Schema& schema) {{\
                return schema.{name}; }}", file=out)

