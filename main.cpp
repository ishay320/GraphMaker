#include <filesystem>
#include <iostream>
#include <string>
#include <vector>

/**
 * @brief Get the Files By Filter
 *
 * @param path the path to the folder
 * @param extensions of the files
 * @param excludes folders to exclude - relative to program
 * @return std::vector<std::filesystem::directory_entry>
 */
std::vector<std::filesystem::directory_entry> getFilesByFilter(const std::string path, const std::vector<std::string> extensions,
                                                               const std::vector<std::string> excludes = {})
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

int main(int argc, char const* argv[])
{
    // Input parsing
    if (argc < 2)
    {
        std::cout << "Usage: " << argv[0] << " <path> [exclude list]\n";
        return 1;
    }

    std::string path = argv[1];

    std::vector<std::string> excludes;
    for (size_t i = 2; i < argc; i++)
    {
        excludes.emplace_back(argv[i]);
    }

    std::vector<std::string> extensions{".cpp", ".hpp", ".c", ".h"};

    std::vector<std::filesystem::directory_entry> files = getFilesByFilter(path, extensions, excludes);

    for (auto&& file : files)
    {
        std::cout << file.path() << '\n';
    }

    return 0;
}
