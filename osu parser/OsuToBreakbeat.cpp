#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <map>
#include <regex>

struct NoteData {
    std::vector<int> hitTimes;
    std::vector<int> longNoteTimes;
    std::vector<int> releaseTimes;
};

void ParseOsuFile(const std::string& osuFilePath, const std::string& outputFilePath) {
    std::ifstream osuFile(osuFilePath);
    std::ofstream outputFile(outputFilePath);
    std::string line;
    std::regex hitObjectRegex(R"((\d+),(\d+),(\d+),(\d+),(\d+),?([^,]*))");
    std::smatch match;
    
    std::map<int, NoteData> noteColumns;
    const int numColumns = 4; // Adjust based on the osu! map format
    int columnWidth = 512 / numColumns;
    
    while (std::getline(osuFile, line)) {
        if (std::regex_match(line, match, hitObjectRegex)) {
            int x = std::stoi(match[1].str());
            int time = std::stoi(match[3].str());
            int type = std::stoi(match[4].str());
            
            int columnIndex = x / columnWidth;
            
            if (type & 1) { // Normal hit object
                noteColumns[columnIndex].hitTimes.push_back(time);
            }
            if (type & 128) { // Long note
                int releaseTime = std::stoi(match[6].str());
                noteColumns[columnIndex].longNoteTimes.push_back(time);
                noteColumns[columnIndex].releaseTimes.push_back(releaseTime);
            }
        }
    }
    
    for (const auto& [columnIndex, data] : noteColumns) {
        outputFile << columnIndex + 1 << " Column Hit Times:" << std::endl;
        for (const int& time : data.hitTimes) {
            outputFile << time << "," << std::endl;
        }
        outputFile << std::endl;
        
        outputFile << columnIndex + 1 << " Column Long Note Times:" << std::endl;
        for (const int& time : data.longNoteTimes) {
            outputFile << time << "," << std::endl;
        }
        outputFile << std::endl;
        
        outputFile << columnIndex + 1 << " Column Release Times:" << std::endl;
        for (const int& time : data.releaseTimes) {
            outputFile << time << "," << std::endl;
        }
        outputFile << std::endl;
    }
}

int main() {
    std::string osuFilePath = "Kurokotei - Galaxy Collapse (Mat) [Cataclysmic Hypernova].osu";
    std::string outputFilePath = "Kurokotei - Galaxy Collapse (Mat) [Cataclysmic Hypernova].osu.txt";
    ParseOsuFile(osuFilePath, outputFilePath);
    std::cout << "Parsing complete. Output saved to " << outputFilePath << std::endl;
    return 0;
}
