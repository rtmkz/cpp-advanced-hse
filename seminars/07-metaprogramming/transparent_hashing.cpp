#include <functional>
#include <string_view>
#include <unordered_map>
#include <string>

using namespace std::string_literals;
using namespace std::string_view_literals;

/// Accept various types of arguments for better API and no allocations
struct StringHash
{
    using hash_type = std::hash<std::string_view>;
    using is_transparent = void;
 
    size_t operator()(std::string_view str) const { return hash_type{}(str); }
    size_t operator()(const std::string& str) const { return hash_type{}(str); }
};

void DoStuff() {
    std::unordered_map<std::string, size_t> map;
    std::unordered_map<std::string, size_t, StringHash, std::equal_to<>> other;

    /// map.find("string view"sv);  // compile error
    map.find(std::string{"string view"sv}); // temporary object
    map.find("std::string"s);

    other.find("string view"sv); // no temporary object
    other.find("std::string"s);
}
