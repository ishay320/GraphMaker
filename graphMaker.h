#include <filesystem>
#include <fstream>
#include <iostream>
#include <string>
#include <vector>

typedef struct
{
    std::string include_file;
    bool quotation_marks;
} Include;

/**
 * @brief Get the Include name and type from line
 *
 * @param line string with the line
 * @param include to fill with file name and type
 * @returns true if had #include with file
 */
bool getInclude(const std::string& line, Include& include);

/**
 * @brief Print the files and their includes into a mermaid graph
 *
 * @param out the output
 * @param files list of all the files
 */
void printIncludeGraph(std::ostream& out, const std::vector<std::filesystem::directory_entry>& files);

std::string getRandomColor();

std::string getRandomFromList(std::vector<std::string>& list);

inline std::vector<std::string> colors{"blue",  "black", "silver", "red",    "purple", "white", "maroon", "fuchsia",
                                       "green", "lime",  "olive",  "yellow", "navy",   "gray",  "teal",   "aqua"};