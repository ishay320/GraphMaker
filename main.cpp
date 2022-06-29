#include <filesystem>
#include <fstream>
#include <iostream>
#include <string>
#include <vector>

#include "utils.h"

typedef struct
{
    std::string include_file;
    bool quotation_marks;
    size_t line;
} Include;

/**
 * @brief Get the Include name and type from line
 *
 * @param line string with the line
 * @param include to fill with file name and type
 * @returns true if had #include with file
 */
bool getInclude(const std::string& line, Include& include);

int main(int argc, char const* argv[])
{
    // Input parsing
    if (argc < 2)
    {
        std::cout << "Usage: " << argv[0] << " <path> [exclude list]\n";
        return 1;
    }

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

    // Print the files and their includes
    for (auto&& file : files)
    {
        std::cout << file.path() << '\n';

        std::ifstream in_file{file.path()};
        std::string line; // TODO: get line number
        while (std::getline(in_file, line))
        {
            Include tmp;
            if (getInclude(line, tmp))
            {
                std::cout << std::setw(15) << std::left << tmp.include_file;
                std::cout << (tmp.quotation_marks ? "local file" : "system file") << '\n';
            }
        }
        in_file.close();
    }

    return 0;
}

bool getInclude(const std::string& line, Include& include)
{
    std::string clean_line = utils::removeWhiteSpaces(line);
    bool had_include       = false;

    // Check if #include is on the start
    if (clean_line.size() > 0 && clean_line[0] == '#')
    {
        bool has_include      = false;
        size_t filename_start = -1;
        bool quotation        = false;

        std::string word = "#include";
        size_t word_pos  = 0;
        for (size_t i = 0; i < clean_line.size(); i++)
        {
            // Check for #include at the start
            if (!has_include)
            {
                if (clean_line[i] == word[word_pos])
                {
                    word_pos++;
                }
                else if (clean_line[i] == ' ' || clean_line[i] == '\t')
                {
                    continue;
                }
                if (word_pos == word.size())
                {
                    has_include = true;
                }
                continue;
            }

            if (clean_line[i] == ' ' || clean_line[i] == '\t')
            {
                continue;
            }

            // Get the file name
            if (clean_line[i] == '<')
            {
                include.quotation_marks = false;
                filename_start          = i;
            }
            else if (clean_line[i] == '"' && !quotation)
            {
                quotation               = true;
                include.quotation_marks = true;
                filename_start          = i;
            }
            else if (clean_line[i] == '>' && include.quotation_marks == false)
            {
                include.include_file = clean_line.substr(filename_start + 1, i - filename_start - 1);
                had_include          = true;
                break;
            }
            else if (clean_line[i] == '"' && include.quotation_marks == true)
            {
                include.include_file = clean_line.substr(filename_start + 1, i - filename_start - 1);
                had_include          = true;
                break;
            }
        }
    }
    return had_include;
}