#include <filesystem>
#include <iostream>
#include <string>
#include <vector>

#include "utils.h"

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

    std::vector<std::filesystem::directory_entry> files = utils::getFilesByFilter(path, extensions, excludes);

    for (auto&& file : files)
    {
        std::cout << file.path() << '\n';
    }

    return 0;
}
