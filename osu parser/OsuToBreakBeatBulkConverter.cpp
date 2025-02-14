#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <map>
#include <regex>
#include <filesystem>

namespace fs = std::filesystem;
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
using std::endl;

// Data structure to store note hit times
struct NoteData {
    vector<int> hitTimes;
    vector<int> longNoteTimes;
    vector<int> releaseTimes;
};

// Function to parse metadata from osu! files
void ParseOsuMetadata(const string& osuFilePath, map<string, string>& metadata) {
    ifstream osuFile(osuFilePath);
    string line;

    while (getline(osuFile, line)) {
        if (line.find("Title:") == 0) metadata["Title"] = line.substr(6);
        else if (line.find("Artist:") == 0) metadata["Artist"] = line.substr(7);
        else if (line.find("AudioFilename:") == 0) metadata["Audio"] = line.substr(15);
        else if (line.find("Version:") == 0) metadata["Difficulty"] = line.substr(8);
        else if (line.find("Background and Video events") != string::npos) {
            while (getline(osuFile, line) && line.find("//") != 0) {
                std::smatch match;
                regex bgRegex(R"(0,0,\"([^\"]+)\")");
                if (regex_search(line, match, bgRegex)) {
                    metadata["Background"] = match[1];
                    break;
                }
            }
        }
        else if (line.find("[HitObjects]") != string::npos) {
            break; // Stop once we reach the hit objects
        }
    }
}

// Function to parse hit objects from an osu! file
void ParseOsuHitObjects(const string& osuFilePath, map<int, NoteData>& noteColumns) {
    ifstream osuFile(osuFilePath);
    string line;
    regex hitObjectRegex(R"((\d+),(\d+),(\d+),(\d+),(\d+),?([^,]*))");
    smatch match;
    
    const int numColumns = 4;
    int columnWidth = 512 / numColumns;

    while (getline(osuFile, line)) {
        if (regex_match(line, match, hitObjectRegex)) {
            int x = stoi(match[1].str());
            int time = stoi(match[3].str());
            int type = stoi(match[4].str());

            int columnIndex = x / columnWidth;

            if (type & 1) { // Normal hit object
                noteColumns[columnIndex].hitTimes.push_back(time);
            }
            if (type & 128) { // Long note
                if(match[6].str() == "")
                    continue;
                int releaseTime = stoi(match[6].str());
                noteColumns[columnIndex].longNoteTimes.push_back(time);
                noteColumns[columnIndex].releaseTimes.push_back(releaseTime);
            }
        }
    }
}

// Function to generate Breakbeat format metadata
void WriteBreakbeatMetadata(const string& outputPath, const map<string, string>& metadata, const map<int, NoteData>& noteColumns) {
    ofstream outputFile(metadata.at("Difficulty")+".txt");

    if (metadata.empty()) {
        cout << "Skipping: Invalid or non-Mania osu! file.\n";
        return;
    }

    string artist = metadata.at("Artist");
    string title = metadata.at("Title");
    string audioPath = "charts\\" + artist + "-" + title + "\\" + metadata.at("Audio");
    string bgPath = "charts\\" + artist + "-" + title + "\\" + metadata.at("Background");

    outputFile << "Artist : " << artist << endl;
    outputFile << "Song Name : " << title << endl;
    outputFile << "Difficulty : " << 0 << endl;
    outputFile << "BPM : 190" << endl; // Placeholder (extracting BPM can be added)
    outputFile << "Background Image : " << bgPath << endl;
    outputFile << "Audio : " << audioPath << endl;
    outputFile << endl;

    for (const auto& [columnIndex, data] : noteColumns) {
        outputFile << columnIndex + 1 << " Column Hit Times:" << endl;
        for (const int& time : data.hitTimes) outputFile << time << "," << endl;
        outputFile << endl;

        outputFile << columnIndex + 1 << " Column Long Note Times:" << endl;
        for (const int& time : data.longNoteTimes) outputFile << time << "," << endl;
        outputFile << endl;

        outputFile << columnIndex + 1 << " Column Release Times:" << endl;
        for (const int& time : data.releaseTimes) outputFile << time << "," << endl;
        outputFile << endl;
    }
}

void ProcessOsuFiles(const string& directory) {
    for (const auto& entry : fs::directory_iterator(directory)) {
        if (entry.path().extension() == ".osu") {
            std::filesystem::path outputFilePath = entry.path().filename();
            outputFilePath.replace_extension(".txt"); // Now it's modifiable
            
            map<string, string> metadata;
            map<int, NoteData> noteColumns;

            ParseOsuMetadata(entry.path().string(), metadata);
            if (!metadata.empty()) {
                ParseOsuHitObjects(entry.path().string(), noteColumns);
                WriteBreakbeatMetadata(outputFilePath.string(), metadata, noteColumns);
                cout << "Processed: " << entry.path().string() << " -> " << outputFilePath << endl;
            }
        }
    }
}

int main() {
    string directory = "C:\\Users\\deeza\\AppData\\Local\\osu!\\Songs\\576426 BaconAkin - Yeah Boy - Shooting Stars [no video]";
    ProcessOsuFiles(directory);
    return 0;
}
