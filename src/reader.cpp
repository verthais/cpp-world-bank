#include "reader.h"

#include <thread>
#include <mutex>
#include <iostream>

Reader::Reader(const std::string& source, std::map<std::string, std::vector<Project>>& records) noexcept
    : m_io(source)
    , m_records(records)
{}

Reader::~Reader()
{
    m_io.close();
}

Reader::operator bool() const noexcept
{
    return m_io.is_open();
}

void
Reader::load() noexcept
{
    std::vector<std::thread> parsers;
    std::mutex m;

    for(int i{}; i < 8; ++i)
    {
        parsers.emplace_back([this, &m](){
            std::string line;
            while(m_io)
            {
                {
                    std::scoped_lock lock(m);
                    std::getline(m_io,line);
                }

                auto project = Project::from(line);

                if(std::scoped_lock lock(m); project)
                {
                    auto itr = m_records.find(project->region);
                    if(itr == m_records.end())
                    {
                        m_records[project->region] = {};
                    }
                    m_records[project->region].push_back(*project);
                }
            }
        });
    }

    for(auto& parser : parsers)
    {
        if(parser.joinable())
            parser.join();
    }
}