#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <map>
#include <regex>

using std::vector;
using std::ifstream;
using std::ofstream;
using std::regex;
using std::string;
using std::smatch;
using std::stoi;
using std::map;
using std::getline;
using std::regex_match;
using std::cout;

// Data structure to store the regular note hit times, long note times and release times
struct NoteData {
    vector<int> hitTimes;
    vector<int> longNoteTimes;
    vector<int> releaseTimes;
};

// Function to extract the hit times from an .osu file
void ParseOsuFile(const string& osuFilePath, const string& outputFilePath) {
    // Input stream into the the file to be read
    ifstream osuFile(osuFilePath);
    // Output stream into file to be written to (creates a new file)
    ofstream outputFile(outputFilePath);
    // String data structure to temporarily store a line within the file as a string
    string line;
    // This is where the parsing happens
    // The regular expression pattern to determine the data to extract from the osu hit objects
    regex hitObjectRegex(R"((\d+),(\d+),(\d+),(\d+),(\d+),?([^,]*))");
    // Storing and returning the data when a match for the regular expression is found.
    smatch match;
    
    // Store the NoteData in a hash table with the column number as the index
    map<int, NoteData> noteColumns;
    const int numColumns = 4;
    // Osu's column numbers are based on the 512 divided by the number of columns
    int columnWidth = 512 / numColumns;
    
    // Read the .osu file line by line
    while (getline(osuFile, line)) {
        // Check if the line meets the regular expression pattern
        if (regex_match(line, match, hitObjectRegex)) {
            // The value of the note column
            int x = stoi(match[1].str());
            // The hit timing
            int time = stoi(match[3].str());
            // The type of note it is i.e is it a long note
            int type = stoi(match[4].str());
            
            // The column index
            int columnIndex = x / columnWidth;
            
            if (type & 1) { // Normal hit object
                noteColumns[columnIndex].hitTimes.push_back(time);
            }
            if (type & 128) { // Long note
                int releaseTime = stoi(match[6].str());
                noteColumns[columnIndex].longNoteTimes.push_back(time);
                noteColumns[columnIndex].releaseTimes.push_back(releaseTime);
            }
        }
    }
    
    // Output the data based on the note column
    for (const auto& [columnIndex, data] : noteColumns) {
        outputFile << columnIndex + 1 << " Column Hit Times:" << '\n';
        for (const int& time : data.hitTimes) {
            outputFile << time << "," << '\n';
        }
        outputFile << '\n';
        
        outputFile << columnIndex + 1 << " Column Long Note Times:" << '\n';
        for (const int& time : data.longNoteTimes) {
            outputFile << time << "," << '\n';
        }
        outputFile << '\n';
        
        outputFile << columnIndex + 1 << " Column Release Times:" << '\n';
        for (const int& time : data.releaseTimes) {
            outputFile << time << "," << '\n';
        }
        outputFile << '\n';
    }
}

int main() {
    string osuFilePath = "Kurokotei - Galaxy Collapse (Mat) [Cataclysmic Hypernova].osu";
    string outputFilePath = "Kurokotei - Galaxy Collapse (Mat) [Cataclysmic Hypernova].osu.txt";
    ParseOsuFile(osuFilePath, outputFilePath);
    cout << "Parsing complete. Output saved to " << outputFilePath << '\n';
    return 0;
}
