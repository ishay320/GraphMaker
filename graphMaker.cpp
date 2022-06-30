#include "graphMaker.h"
#include "utils.h"

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

void printIncludeGraph(std::ostream& out, const std::vector<std::filesystem::directory_entry>& files)
{
    // Add the graph mermaid title
    out << "graph TD\n";

    for (size_t i = 0; i < files.size(); i++)
    {
        out << "\n    " << files[i].path().filename().c_str() << '(' << files[i].path().filename().c_str() << ')' << '\n';

        std::ifstream in_file{files[i].path()};
        std::string line;
        while (std::getline(in_file, line))
        {
            Include tmp;
            if (getInclude(line, tmp))
            {
                // From
                out << "    " << files[i].path().filename().c_str() << " --> ";
                // Label
                out << (tmp.quotation_marks ? "|local|" : "|system|") << ' ';
                // To
                out << tmp.include_file << '\n';
            }
        }
        in_file.close();
    }
}