#ifndef PRINTER_H
#define PRINTER_H

#include <map>
#include <vector>

#include "project.h"

namespace Printer
{
    void print_top_regions(const std::map<std::string, std::vector<Project>>&);
    void print_top_cost(const std::map<std::string, std::vector<Project>>&);
}

#endif // PRINTER_H