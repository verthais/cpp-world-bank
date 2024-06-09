#ifndef READER_H
#define READER_H

#include <fstream>
#include <string>
#include <map>
#include <vector>

#include "project.h"

class Reader
{
public:
    explicit Reader(const std::string& source, std::map<std::string, std::vector<Project>>& records) noexcept;
    ~Reader();

    operator bool() const noexcept;
    void load() noexcept;

private:
    std::ifstream m_io;    
    std::map<std::string, std::vector<Project>>& m_records;
};

#endif // READER_H