from random import choice
import string

fields = 2048

def word():
   letters = string.ascii_lowercase
   return ''.join(choice(letters) for i in range(8))

types = [
    "char", "signed char", "unsigned char",
    "int", "long", "bool", "std::string_view",
    "std::vector<int>", "double", "float", "short",
    "Schema *", "void *", "size_t", "char8_t" ]

modif = [ "", "const ",
    "volatile ", "const volatile " ]

res = [(choice(types), choice(modif), word()) for _ in range(fields)]

with open("schema.h", "w") as schema:
    print("#include <string_view>\n#include <vector>\n\nstruct Schema {", file=schema)
    print("    // TODO FIXME decompose", file=schema)

    for t, m, n in res:
        print(f"    {m}{t} {n};", file=schema)

    print("};", file=schema)

with open("test.cpp", "w") as test:
    print('#include <catch.hpp>\n#include "reflection.h"\n', file=test)
    print('TEST_CASE("Reflection") {\n    Schema schema{};\n', file=test)

    for i, (t, m, n) in enumerate(res):
        print(f"    REQUIRE(std::is_same_v<{m}{t}&, decltype(Get<{i}>(schema))>);", file=test)

    print("}", file=test)
