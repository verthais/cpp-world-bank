#include <variant>
#include <vector>
#include <map>

#include "tokenizer.h"

#ifndef JSON_H
#define JSON_H

namespace JSON
{
    class Value;
    using Object = std::map<std::string, Value>;
    using Array = std::vector<Value>;
    class Value : public std::variant<bool, double, std::string, Array, Object> {};

    Object from(const std::string& source);
    std::string serialize(const Object& json);
}

#endif // JSON_H