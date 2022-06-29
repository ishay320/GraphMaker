#include "utils.h"

namespace utils
{

std::vector<std::filesystem::directory_entry> getFilesByFilter(const std::string path, const std::vector<std::string> extensions,
                                                               const std::vector<std::string> excludes)
{
    std::vector<std::filesystem::directory_entry> files;
    std::filesystem::recursive_directory_iterator rdi(path);
    for (const std::filesystem::directory_entry& entry : rdi)
    {
        if (entry.is_directory())
        {
            for (auto&& exclude : excludes)
            {
                if (entry.path() == exclude)
                {
                    rdi.disable_recursion_pending();
                }
            }
        }
        else if (entry.is_regular_file())
        {
            for (const std::string& extension : extensions)
            {
                if (entry.path().filename().extension() == extension)
                {
                    files.push_back(entry);
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