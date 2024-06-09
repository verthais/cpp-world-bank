
#include "json.h"

#include <iostream>
#include <mutex>

namespace JSON
{

Value
valueFromToken(Tokenizer::Iterator& itr)
{
    if('"' == (*itr).at(0))
    {
        return { std::string{*itr} };
    }
    else if('[' == (*itr).at(0))
    {
        ++itr;
        Array array{};

        while("]" != *itr)
        {
            array.emplace_back(valueFromToken(itr));
            ++itr;
        }

        return { std::move(array) };
    }
    else if('{' == (*itr).at(0))
    {
        ++itr;
        Object obj{};

        while("}" != *itr)
        {
            auto key = *itr;
            ++itr;

            auto value = valueFromToken(itr);
            ++itr;

            obj.emplace(std::move(key), std::move(value));
        }

        return { std::move(obj) };
    }
    else
    {
        return { std::atof( std::string{*itr}.c_str() ) };
    }
}

Object
from(const std::string& source)
{
    if(source.empty()) return {};

    static std::mutex m{};

    {
        std::scoped_lock lock{m};
        std::cout << std::endl
            << source
            << std::endl;
    }

    Tokenizer t(source);
    auto itr = t.begin();
    auto end = t.end();

    ++itr; // skip initial "{"
    Object root{};

    // while(end != itr)
    while("}" != *itr)
    {
        auto key = *itr;
        ++itr;

        auto value = valueFromToken(itr);
        ++itr;

        root.emplace(std::move(key), std::move(value));
    }

    return std::move(root);
}

struct visitor
{
    std::string operator()(const std::string& value)
    {
        return value;
    }

    std::string operator()(const double& value)
    {
        if(value - (int) value)
        {
            return std::to_string(value);
        }
        else
        {
            return std::to_string((int)value);
        }
    }

    std::string operator()(const Array& value)
    {
        std::string rv{"["};
        std::string separator{""};
        visitor vis;

        for(const auto& v : value)
        {
            rv += separator + vis(v);
            separator = ",";
        }

        rv += "]";
        return rv;
    }

    std::string operator()(const Object& value)
    {
        std::string rv{"{"};
        std::string separator{""};
        visitor vis;

        for(const auto& [k, v] : value)
        {
            rv += separator + k + ":" + vis(v);
            separator = ",";
        }

        rv += "}";
        return rv;
    }

    std::string operator()(const Value& value)
    {
        std::string rv{};
        visitor vis;

        switch(value.index())
        {
            case 0:
                rv = vis(std::get<0>(value));
            break;
            case 1:
                rv = vis(std::get<1>(value));
            break;
            case 2:
                rv = vis(std::get<2>(value));
            break;
            case 3:
                rv = vis(std::get<3>(value));
            break;
            case 4:
                rv = vis(std::get<4>(value));
            break;
        }

        return rv;
    }
};

std::string serialize(const Object& json)
{
    std::string json_str{"{"};
    std::string separator{""};
    visitor vis;

    for(const auto& [key, value] : json)
    {
        json_str += separator + key + ":" + vis(value);
        separator = ",";
    }

    json_str += "}";
    return json_str;
}
}