#include <filesystem>
#include <fstream>
#include <iostream>
#include <string>
#include <vector>

#include "graphMaker.h"
#include "utils.h"

int main(int argc, char const* argv[])
{
    // Input parsing
    if (argc < 2)
    {
        std::cout << "Usage: " << argv[0] << " <path> [exclude list]\n";
        return 1;
    }
    std::cout << "Starting to make your graph!\n";

    // Path to the search folder
    std::string path = argv[1];

    // Folders to exclude
    std::vector<std::string> excludes;
    for (size_t i = 2; i < argc; i++)
    {
        excludes.emplace_back(argv[i]);
    }

    // Extensions to search
    std::vector<std::string> extensions{".cpp", ".hpp", ".c", ".h"};

    std::vector<std::filesystem::directory_entry> files = utils::getFilesByFilter(path, extensions, excludes);

    std::ofstream output_file{"includes.txt", std::ofstream::out | std::ofstream::trunc};
    printIncludeGraph(output_file, files);

    std::cout << "Done!\n";
    return 0;
}
