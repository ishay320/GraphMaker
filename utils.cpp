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

} // namespace utils