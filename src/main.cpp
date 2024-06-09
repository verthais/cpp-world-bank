#include <map>
#include <vector>
#include <iostream>

#include "project.h"
#include "printer.h"
#include "reader.h"

using namespace std;

int main(int argc, const char* argv[])
{
    if(argc != 2) {
        cerr << "Missing path to data file." << endl;
        cerr << "Usage:\n"
             << "\t./interview {file-path}"
             << endl;
        return 1;
    }


    std::map<std::string, std::vector<Project>> records;
    Reader wb(argv[1], records);

    if(wb){
        wb.load();

        Printer::print_top_regions(records);
        Printer::print_top_cost(records);
    }

    return 0;
}