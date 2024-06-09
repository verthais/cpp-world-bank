#ifndef PROJECT_H
#define PROJECT_H

#include <string>
#include <memory>
#include <optional>

#include "tokenizer.h"

struct Project
{
    std::string id;
    std::string region;
    std::string country;
    long long cost;

    static std::optional<Project> from(const std::string& source);

    const std::string str() const
    {
        return "{ id: \"" + id + "\", country: \"" + country + "\", cost: " + std::to_string(cost) + " }";
    }
};

#endif