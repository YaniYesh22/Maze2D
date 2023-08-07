
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

#include "File.hpp"
#include <filesystem>

void showFilesAndDirectoriesInPath(const std::string &path)
{
    try
    {
        for (const auto &entry : std::__fs::filesystem::directory_iterator(path))
        {
            if (entry.is_regular_file() || entry.is_directory())
            {
                std::cout << entry.path().filename() << std::endl;
            }
        }
    }
    catch (const std::__fs::filesystem::filesystem_error &ex)
    {
        std::cerr << "Error: " << ex.what() << std::endl;
    }
}

void saveCompressedMazeToFile(const std::string &compressedMaze, const std::string &filename)
{
    std::ofstream outputFile(filename);
    if (!outputFile.is_open())
    {
        throw std::runtime_error("Error opening file: " + filename);
    }

    outputFile << compressedMaze << "\n";
    std::cout << "Comppresed mazes saved to file " << std::endl;
    outputFile.close();
}
