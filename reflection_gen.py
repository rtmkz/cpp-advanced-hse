from random import choice
import string

def word():
   letters = string.ascii_lowercase
   return ''.join(choice(letters) for i in range(8))

types = [
    "char",
    "signed char",
    "unsigned char",
    "int",
    "long",
    "bool",
    "std::string_view",
    "std::vector<int>",
    "double",
    "float",
    "short",
    "Schema *",
    "void *"
]

modif = [
    "",
    "const ",
    "volatile ",
    "const volatile "
]

res = []

for i in range(2048):
    t = choice(types)
    m = choice(modif)
    n = word()

    res.append((t, m, n))

print(
    """
#include <string_view>
#include <vector>

struct Schema {
    """)

for t, m, n in res:
    print(f"{m}{t} {n};")

print("}\n")

for i, (t, m, n) in enumerate(res):
    print(f"REQUIRE(std::is_same_v<{m}{t}, decltype(Get<{i}>(schema))>);")
