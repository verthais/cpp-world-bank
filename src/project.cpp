#include "project.h"
#include "tokenizer.h"
#include "json.h"

std::optional<Project>
Project::from(const std::string& source)
{
    std::optional<Project> project;
    Tokenizer t(source);

    if(t.begin() != t.end())
        project = Project();

    for(auto itr = t.begin(); itr != t.end(); ++itr)
    {
        if(*itr == "\"id\"")
        {
            ++itr;
            project->id = *itr; 
        }
        else if(*itr == "\"countryshortname\"")
        {
            ++itr;
            project->country = *itr;
        }
        else if(*itr == "\"regionname\"")
        {
            ++itr;
            project->region = *itr;
        }
        else if(*itr == "\"totalcommamt\"")
        {
            ++itr;
            project->cost = atoll( std::string(*itr).c_str() );
        }
    }   

    return project;
}