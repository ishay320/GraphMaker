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

} // namespace utils