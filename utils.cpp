#include "utils.h"
#include <iostream>
#include <string.h>

namespace utils
{
// remove / from the end
const std::vector<std::string> fixExcludes(const std::vector<std::string> excludes)
{
    std::vector<std::string> fixed_excludes;
    for (auto& exclude : excludes)
    {
        if (exclude.back() == '/' || exclude.back() == '\\')
        {
            std::string tmp{exclude};
            tmp.pop_back();
            fixed_excludes.push_back(tmp);
        }
        else
        {
            fixed_excludes.emplace_back(std::string(exclude));
        }
    }
    return fixed_excludes;
}

std::vector<std::filesystem::directory_entry> getFilesByFilter(const std::string path, const std::vector<std::string> extensions,
                                                               const std::vector<std::string> excludes)
{
    std::vector<std::filesystem::directory_entry> files;
    std::filesystem::recursive_directory_iterator entry(path);
    for (; entry != std::filesystem::recursive_directory_iterator(); ++entry)
    {
        if (entry->is_directory())
        {
            for (auto&& exclude : fixExcludes(excludes))
            {
                if (strncmp(entry->path().c_str(), exclude.c_str(), exclude.size()) == 0)
                {
                    entry.disable_recursion_pending();
                }
            }
        }
        else if (entry->is_regular_file())
        {
            for (const std::string& extension : extensions)
            {
                if (entry->path().filename().extension() == extension)
                {
                    files.push_back(*entry);
                }
            }
        }
    }

    return files;
}

std::vector<std::string> split(const std::string& line, char delim)
{
    std::vector<std::string> result;
    std::stringstream ss(line);
    std::string item;

    while (getline(ss, item, delim))
    {
        result.push_back(item);
    }

    return result;
}

std::string removeWhiteSpaces(const std::string& line)
{
    std::string result;
    bool start = true;

    // remove: start, end, double spaces
    for (size_t i = 0; i < line.size(); i++)
    {
        if (i + 1 < line.size() && line[i] == ' ' && line[i + 1] == ' ')
        {
            continue;
        }

        if (start)
        {
            if ((line[i] == ' ' || line[i] == '\t'))
            {
                continue;
            }
            start = false;
        }
        if (i + 1 == line.size() && line[i] == ' ')
        {
            continue;
        }

        result.push_back(line[i]);
    }

    return result;
}

} // namespace utils