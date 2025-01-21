#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <string>

using namespace std;

// Function to process a line and populate the appropriate column vector
void processLine(const string& line, vector<float>& col1, vector<float>& col2, vector<float>& col3, vector<float>& col4) {
    stringstream ss(line);
    string x, y, timeStr, type, hitSound;

    // Extract components of the line (comma-separated)
    getline(ss, x, ',');
    getline(ss, y, ',');
    getline(ss, timeStr, ',');
    getline(ss, type, ',');
    getline(ss, hitSound, ',');

    // Convert extracted data to integers
    int xPos = stoi(x);
    float time = stof(timeStr);

    // Determine the column based on the x position and add the time to the appropriate vector
    if (xPos == 64) {
        col1.push_back(time);
    } else if (xPos == 192) {
        col2.push_back(time);
    } else if (xPos == 320) {
        col3.push_back(time);
    } else if (xPos == 448) {
        col4.push_back(time);
    }
}

int main() {
    // File path to the .osu file
    string filePath = "Sharkey & Arkitech - Quadraphinix (Xay) [Challenge 0.75x (135bpm) OD8].osu";

    // Vectors for each column
    vector<float> firstColumnNoteHitTimes;
    vector<float> secondColumnNoteHitTimes;
    vector<float> thirdColumnNoteHitTimes;
    vector<float> fourthColumnNoteHitTimes;

    // Open the .osu file
    ifstream file(filePath);
    if (!file.is_open()) {
        cerr << "Error: Unable to open file " << filePath << endl;
        return 1;
    }

    string line;
    bool hitObjectsSection = false;

    // Read the file line by line
    while (getline(file, line)) {
        // Check if we've reached the [HitObjects] section
        if (line == "[HitObjects]") {
            hitObjectsSection = true;
            continue;
        }

        // Skip lines until we reach the [HitObjects] section
        if (!hitObjectsSection) continue;

        // Process the line to extract note data
        processLine(line, firstColumnNoteHitTimes, secondColumnNoteHitTimes, thirdColumnNoteHitTimes, fourthColumnNoteHitTimes);
    }

    file.close();

    // Output the results
    cout << "vector<float> firstColumnNoteHitTimes = { ";
    for (size_t i = 0; i < firstColumnNoteHitTimes.size(); ++i) {
        cout << firstColumnNoteHitTimes[i];
        if (i != firstColumnNoteHitTimes.size() - 1) cout << ", ";
    }
    cout << " };" << "\n";

    cout << "vector<float> secondColumnNoteHitTimes = { ";
    for (size_t i = 0; i < secondColumnNoteHitTimes.size(); ++i) {
        cout << secondColumnNoteHitTimes[i];
        if (i != secondColumnNoteHitTimes.size() - 1) cout << ", ";
    }
    cout << " };" << "\n";

    cout << "vector<float> thirdColumnNoteHitTimes = { ";
    for (size_t i = 0; i < thirdColumnNoteHitTimes.size(); ++i) {
        cout << thirdColumnNoteHitTimes[i];
        if (i != thirdColumnNoteHitTimes.size() - 1) cout << ", ";
    }
    cout << " };" << "\n";

    cout << "vector<float> fourthColumnNoteHitTimes = { ";
    for (size_t i = 0; i < fourthColumnNoteHitTimes.size(); ++i) {
        cout << fourthColumnNoteHitTimes[i];
        if (i != fourthColumnNoteHitTimes.size() - 1) cout << ", ";
    }
    cout << " };" << "\n";

    return 0;
}