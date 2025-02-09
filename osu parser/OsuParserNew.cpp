#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <string>

using namespace std;

// Function to process a line and populate the appropriate vectors for hit and release times
void processLine(const string& line, 
                 vector<float>& hitCol1, vector<float>& hitCol2, vector<float>& hitCol3, vector<float>& hitCol4, 
                 vector<float>& releaseCol1, vector<float>& releaseCol2, vector<float>& releaseCol3, vector<float>& releaseCol4,
                 vector<float>& longHitCol1, vector<float>& longHitCol2, vector<float>& longHitCol3, vector<float>& longHitCol4) {
    stringstream ss(line);
    string x, y, timeStr, type, hitSound, endTimeStr;

    // Extract components of the line (comma-separated)
    getline(ss, x, ',');
    getline(ss, y, ',');
    getline(ss, timeStr, ',');
    getline(ss, type, ',');
    getline(ss, hitSound, ',');

    // Check if there's an end time (only for long notes)
    bool isLongNote = (type == "128" && getline(ss, endTimeStr, ','));

    // Convert extracted data to integers/floats
    int xPos = stoi(x);
    float time = stof(timeStr);
    float endTime = isLongNote ? stof(endTimeStr) : 0.0f;

    // Determine the column based on the x position and add the times to the appropriate vectors
    if (xPos == 64) {
        if (isLongNote) {
            releaseCol1.push_back(endTime);
            longHitCol1.push_back(time);
        } else {
            hitCol1.push_back(time);
        }
    } else if (xPos == 192) {
        if (isLongNote) {
            releaseCol2.push_back(endTime);
            longHitCol2.push_back(time);
        } else {
            hitCol2.push_back(time);
        }
    } else if (xPos == 320) {
        if (isLongNote) {
            releaseCol3.push_back(endTime);
            longHitCol3.push_back(time);
        } else {
            hitCol3.push_back(time);
        }
    } else if (xPos == 448) {
        if (isLongNote) {
            releaseCol4.push_back(endTime);
            longHitCol4.push_back(time);
        } else {
            hitCol4.push_back(time);
        }
    }
}

int main() {
    // File path to the .osu file
    string filePath = "Sharkey & Arkitech - Quadraphinix (Xay) [Challenge].osu";

    // Vectors for hit times, release times, and long note hit times for each column
    vector<float> firstColumnNoteHitTimes, secondColumnNoteHitTimes, thirdColumnNoteHitTimes, fourthColumnNoteHitTimes;
    vector<float> firstColumnNoteReleaseTimes, secondColumnNoteReleaseTimes, thirdColumnNoteReleaseTimes, fourthColumnNoteReleaseTimes;
    vector<float> firstColumnLongNoteHitTimes, secondColumnLongNoteHitTimes, thirdColumnLongNoteHitTimes, fourthColumnLongNoteHitTimes;

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
        processLine(line, firstColumnNoteHitTimes, secondColumnNoteHitTimes, thirdColumnNoteHitTimes, fourthColumnNoteHitTimes,
                    firstColumnNoteReleaseTimes, secondColumnNoteReleaseTimes, thirdColumnNoteReleaseTimes, fourthColumnNoteReleaseTimes,
                    firstColumnLongNoteHitTimes, secondColumnLongNoteHitTimes, thirdColumnLongNoteHitTimes, fourthColumnLongNoteHitTimes);
    }

    file.close();

    // Output the results in noteColumn format
    cout << "NoteColumn firstColumn = {" << endl;
    cout << "0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0," << endl;
    cout << "\"main-gameplay-left-note\"," << endl;
    cout << "581.936, 0," << endl;
    cout << "{ ";
    for (size_t i = 0; i < firstColumnNoteHitTimes.size(); ++i) {
        cout << firstColumnNoteHitTimes[i];
        if (i != firstColumnNoteHitTimes.size() - 1) cout << ", ";
    }
    cout << " }," << endl;
    cout << "{ ";
    for (size_t i = 0; i < firstColumnNoteReleaseTimes.size(); ++i) {
        cout << firstColumnNoteReleaseTimes[i];
        if (i != firstColumnNoteReleaseTimes.size() - 1) cout << ", ";
    }
    cout << " }," << endl;
    cout << "{ ";
    for (size_t i = 0; i < firstColumnLongNoteHitTimes.size(); ++i) {
        cout << firstColumnLongNoteHitTimes[i];
        if (i != firstColumnLongNoteHitTimes.size() - 1) cout << ", ";
    }
    cout << " }," << endl;
    cout << "{}, {}, {}, false, false, false, 0, 0";
    cout << "};" << endl;

    // Repeat for other columns
    // Second column
    cout << "NoteColumn secondColumn = {" << endl;
    cout << "0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0," << endl;
    cout << "\"main-gameplay-down-note\"," << endl;
    cout << "765.423, 0," << endl;
    cout << "{ ";
    for (size_t i = 0; i < secondColumnNoteHitTimes.size(); ++i) {
        cout << secondColumnNoteHitTimes[i];
        if (i != secondColumnNoteHitTimes.size() - 1) cout << ", ";
    }
    cout << " }," << endl;
    cout << "{ ";
    for (size_t i = 0; i < secondColumnNoteReleaseTimes.size(); ++i) {
        cout << secondColumnNoteReleaseTimes[i];
        if (i != secondColumnNoteReleaseTimes.size() - 1) cout << ", ";
    }
    cout << " }," << endl;
    cout << "{ ";
    for (size_t i = 0; i < secondColumnLongNoteHitTimes.size(); ++i) {
        cout << secondColumnLongNoteHitTimes[i];
        if (i != secondColumnLongNoteHitTimes.size() - 1) cout << ", ";
    }
    cout << " }," << endl;
    cout << "{}, {}, {}, false, false, false, 0, 0";
    cout << "};" << endl;
    
    // Third column
    cout << "NoteColumn thirdColumn = {" << endl;
    cout << "0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0," << endl;
    cout << "\"main-gameplay-up-note\"," << endl;
    cout << "949.361, 0," << endl;
    cout << "{ ";
    for (size_t i = 0; i < thirdColumnNoteHitTimes.size(); ++i) {
        cout << thirdColumnNoteHitTimes[i];
        if (i != thirdColumnNoteHitTimes.size() - 1) cout << ", ";
    }
    cout << " }," << endl;
    cout << "{ ";
    for (size_t i = 0; i < thirdColumnNoteReleaseTimes.size(); ++i) {
        cout << thirdColumnNoteReleaseTimes[i];
        if (i != thirdColumnNoteReleaseTimes.size() - 1) cout << ", ";
    }
    cout << " }," << endl;
    cout << "{ ";
    for (size_t i = 0; i < thirdColumnLongNoteHitTimes.size(); ++i) {
        cout << thirdColumnLongNoteHitTimes[i];
        if (i != thirdColumnLongNoteHitTimes.size() - 1) cout << ", ";
    }
    cout << " }," << endl;
    cout << "{}, {}, {},false, false, false, 0, 0";
    cout << "};" << endl;
    
    // Fourth column
    cout << "NoteColumn fourthColumn = {" << endl;
    cout << "0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0," << endl;
    cout << "\"main-gameplay-right-note\"," << endl;
    cout << "1138.061, 0," << endl;
    cout << "{ ";
    for (size_t i = 0; i < fourthColumnNoteHitTimes.size(); ++i) {
        cout << fourthColumnNoteHitTimes[i];
        if (i != fourthColumnNoteHitTimes.size() - 1) cout << ", ";
    }
    cout << " }," << endl;
    cout << "{ ";
    for (size_t i = 0; i < fourthColumnNoteReleaseTimes.size(); ++i) {
        cout << fourthColumnNoteReleaseTimes[i];
        if (i != fourthColumnNoteReleaseTimes.size() - 1) cout << ", ";
    }
    cout << " }," << endl;
    cout << "{ ";
    for (size_t i = 0; i < fourthColumnLongNoteHitTimes.size(); ++i) {
        cout << fourthColumnLongNoteHitTimes[i];
        if (i != fourthColumnLongNoteHitTimes.size() - 1) cout << ", ";
    }
    cout << " }," << endl;
    cout << "{}, {}, {},false, false, false, 0, 0";
    cout << "};" << endl;

    return 0;
}
