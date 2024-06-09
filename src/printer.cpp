#include "printer.h"
#include <iostream>
#include <set>
#include <algorithm>

namespace Printer
{

struct comparator
{
	template<typename T>
	bool operator()(const T& lhs, const T& rhs) const noexcept
	{
		if (lhs.second != rhs.second)
			return lhs.second > rhs.second;

		return lhs.first > rhs.first;
	}
};

void print_top_regions(const std::map<std::string, std::vector<Project>>& records)
{
    std::set<std::pair<std::string, size_t>, comparator> top_projects;
    for(const auto& [region, projects] : records)
    {
        top_projects.insert({region, projects.size()});
    }

    std::cout << "Regions by project realization:" << std::endl;
    std::for_each_n(top_projects.begin(), (top_projects.size() > 10) ? 10 : top_projects.size(), [](const auto& e){
        std::cout << "\t" << e.first << ": " << e.second << std::endl;
    });
    std::cout << std::endl;
}

void print_top_cost(const std::map<std::string, std::vector<Project>>& records)
{
    std::set<std::pair<std::string, long long>, comparator> top_cost;
    for(const auto& [region, projects] : records)
    {
        long long sum{};
        for(const auto& p : projects)
            sum += p.cost;
        top_cost.insert({region, sum});
    }

    std::cout << "Regions by cost:" << std::endl;
    std::for_each_n(top_cost.begin(), (top_cost.size() > 10) ? 10 : top_cost.size(), [](const auto& e){
        std::cout << "\t" << e.first << ": " << e.second << std::endl;
    });
    std::cout << std::endl;
}

} // namespace Printer