#include <filesystem>
#include <string>
#include <vector>

namespace utils
{

/**
 * @brief Get the Files By Filter
 *
 * @param path the path to the folder
 * @param extensions of the files
 * @param excludes folders to exclude - relative to program
 * @return std::vector<std::filesystem::directory_entry>
 */
std::vector<std::filesystem::directory_entry> getFilesByFilter(const std::string path, const std::vector<std::string> extensions,
                                                               const std::vector<std::string> excludes = {});

/**
 * @brief removes white spaces from the start and end also double spaces
 *
 * @param line
 * @return std::string
 */
std::string removeWhiteSpaces(const std::string& line);

} // namespace utils