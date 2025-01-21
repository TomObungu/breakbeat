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
    string filePath = "Sharkey & Arkitech - Quadraphinix (Xay) [Challenge 0.75x (135bpm) OD8].osu";

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

    // Output the results for hit times
    cout << "vector<float> firstColumnNoteHitTimes = { ";
    for (size_t i = 0; i < firstColumnNoteHitTimes.size(); ++i) {
        cout << firstColumnNoteHitTimes[i];
        if (i != firstColumnNoteHitTimes.size() - 1) cout << ", ";
    }
    cout << " };" << '\n';

    cout << "vector<float> secondColumnNoteHitTimes = { ";
    for (size_t i = 0; i < secondColumnNoteHitTimes.size(); ++i) {
        cout << secondColumnNoteHitTimes[i];
        if (i != secondColumnNoteHitTimes.size() - 1) cout << ", ";
    }
    cout << " };" << '\n';

    cout << "vector<float> thirdColumnNoteHitTimes = { ";
    for (size_t i = 0; i < thirdColumnNoteHitTimes.size(); ++i) {
        cout << thirdColumnNoteHitTimes[i];
        if (i != thirdColumnNoteHitTimes.size() - 1) cout << ", ";
    }
    cout << " };" << '\n';

    cout << "vector<float> fourthColumnNoteHitTimes = { ";
    for (size_t i = 0; i < fourthColumnNoteHitTimes.size(); ++i) {
        cout << fourthColumnNoteHitTimes[i];
        if (i != fourthColumnNoteHitTimes.size() - 1) cout << ", ";
    }
    cout << " };" << '\n';

    // Output the results for release times
    cout << "vector<float> firstColumnNoteReleaseTimes = { ";
    for (size_t i = 0; i < firstColumnNoteReleaseTimes.size(); ++i) {
        cout << firstColumnNoteReleaseTimes[i];
        if (i != firstColumnNoteReleaseTimes.size() - 1) cout << ", ";
    }
    cout << " };" << '\n';

    cout << "vector<float> secondColumnNoteReleaseTimes = { ";
    for (size_t i = 0; i < secondColumnNoteReleaseTimes.size(); ++i) {
        cout << secondColumnNoteReleaseTimes[i];
        if (i != secondColumnNoteReleaseTimes.size() - 1) cout << ", ";
    }
    cout << " };" << '\n';

    cout << "vector<float> thirdColumnNoteReleaseTimes = { ";
    for (size_t i = 0; i < thirdColumnNoteReleaseTimes.size(); ++i) {
        cout << thirdColumnNoteReleaseTimes[i];
        if (i != thirdColumnNoteReleaseTimes.size() - 1) cout << ", ";
    }
    cout << " };" << '\n';

    cout << "vector<float> fourthColumnNoteReleaseTimes = { ";
    for (size_t i = 0; i < fourthColumnNoteReleaseTimes.size(); ++i) {
        cout << fourthColumnNoteReleaseTimes[i];
        if (i != fourthColumnNoteReleaseTimes.size() - 1) cout << ", ";
    }
    cout << " };" << '\n';

    // Output the results for long note hit times
    cout << "vector<float> firstColumnLongNoteHitTimes = { ";
    for (size_t i = 0; i < firstColumnLongNoteHitTimes.size(); ++i) {
        cout << firstColumnLongNoteHitTimes[i];
        if (i != firstColumnLongNoteHitTimes.size() - 1) cout << ", ";
    }
    cout << " };" << '\n';

    cout << "vector<float> secondColumnLongNoteHitTimes = { ";
    for (size_t i = 0; i < secondColumnLongNoteHitTimes.size(); ++i) {
        cout << secondColumnLongNoteHitTimes[i];
        if (i != secondColumnLongNoteHitTimes.size() - 1) cout << ", ";
    }
    cout << " };" << '\n';

    cout << "vector<float> thirdColumnLongNoteHitTimes = { ";
    for (size_t i = 0; i < thirdColumnLongNoteHitTimes.size(); ++i) {
        cout << thirdColumnLongNoteHitTimes[i];
        if (i != thirdColumnLongNoteHitTimes.size() - 1) cout << ", ";
    }
    cout << " };" << '\n';

    cout << "vector<float> fourthColumnLongNoteHitTimes = { ";
    for (size_t i = 0; i < fourthColumnLongNoteHitTimes.size(); ++i) {
        cout << fourthColumnLongNoteHitTimes[i];
        if (i != fourthColumnLongNoteHitTimes.size() - 1) cout << ", ";
    }
    cout << " };" << '\n';

    return 0;
}
