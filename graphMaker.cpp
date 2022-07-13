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

inline int randomInt(int low, int high) { return low + rand() % (low - high); }

std::string getRandomColor()
{
    int color_dec = randomInt(0, 4095);
    std::stringstream stream;
    stream << '#' << std::setfill('0') << std::setw(3) << std::hex << color_dec;
    std::string color(stream.str());
    return color;
}

std::string getRandomFromList(std::vector<std::string>& list)
{
    int random = rand() % list.size();
    return list[random];
}

std::string getNextFromList(std::vector<std::string>& list, bool get_last = false)
{
    static int pos = 0;
    if (pos >= list.size())
    {
        pos = 0;
    }
    if (get_last)
    {
        if (pos - 1 < 0)
        {
            return list[list.size() - 1];
        }

        return list[pos - 1];
    }

    return list[pos++];
}

void printLineColor(std::ostream& out, int start, int end)
{
    if (start >= end)
    {
        return;
    }
    out << "\tlinkStyle ";
    for (int i = start; i < end; i++)
    {
        out << i;
        if (!(i + 1 == end))
        {
            out << ',';
        }
    }
    out << " stroke-width:2px,fill:none,stroke:" << getNextFromList(colors) << ";\n";
}

void printLineColor(std::ostream& out, const std::string& node_name)
{
    if (node_name.empty())
    {
        return;
    }
    out << "\tstyle " << node_name << " stroke:" << getNextFromList(colors, true) << ";\n";
}

void printIncludeGraph(std::ostream& out, const std::vector<std::filesystem::directory_entry>& files)
{
    // Add the graph mermaid title
    out << "graph TD\n";
    int start = 0;
    int end   = 0;

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
                end++;
            }
        }

        printLineColor(out, start, end);
        if (start != end)
        {
            printLineColor(out, files[i].path().filename().string());
        }

        start = end;
        in_file.close();
    }
}