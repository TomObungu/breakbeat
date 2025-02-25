#include "Game.hpp"
#include <vector>
#include <numeric>
#include <algorithm>
#include <cmath>

using namespace std;

// Function to detect the average interval between note timings
double Game::DetectInterval(const vector<float>& note_times) {
    if (note_times.size() < 2) return 0.0;

    vector<float> intervals;
    for (unsigned i = 1; i < note_times.size(); ++i) {
        intervals.push_back(note_times[i] - note_times[i - 1]);
    }

    return accumulate(intervals.begin(), intervals.end(), 0.0) / intervals.size();
}

// Function to calculate jumpstream difficulty
double Game::CalculateJumpstreamDifficulty(const std::vector<std::vector<float>>& columns) {
    if (columns.size() < 2) return 0.0;

    // Step 1: Identify jumps (two simultaneous notes across different columns)
    std::vector<float> jump_timings;
    for (size_t i = 0; i < columns.size(); ++i) {
        for (size_t j = i + 1; j < columns.size(); ++j) {
            const auto& column1 = columns[i];
            const auto& column2 = columns[j];

            size_t idx1 = 0, idx2 = 0;
            while (idx1 < column1.size() && idx2 < column2.size()) {
                if (std::abs(column1[idx1] - column2[idx2]) <= 1e-3) { // If timings match
                    jump_timings.push_back(column1[idx1]);
                    ++idx1;
                    ++idx2;
                }
                else if (column1[idx1] < column2[idx2]) {
                    ++idx1;
                }
                else {
                    ++idx2;
                }
            }
        }
    }

    // Step 2: Sort jump timings
    std::sort(jump_timings.begin(), jump_timings.end());

    // Step 3: Identify jumpstreams (two consecutive jumps with notes in between)
    std::vector<float> jumpstream_densities;
    for (size_t i = 1; i < jump_timings.size(); ++i) {
        float start_jump = jump_timings[i - 1];
        float end_jump = jump_timings[i];

        // Collect all note timings between the two jumps
        std::vector<float> notes_between_jumps;
        for (const auto& column : columns) {
            for (float note_time : column) {
                if (note_time > start_jump && note_time < end_jump) {
                    notes_between_jumps.push_back(note_time);
                }
            }
        }

        // Calculate the density of the notes between the two jumps
        double density = DetectInterval(notes_between_jumps);
        jumpstream_densities.push_back(density);
   
    }

    // Step 4: Calculate average density of all jumpstreams
    if (jumpstream_densities.empty()) return 0.0;

    double total_density = std::accumulate(jumpstream_densities.begin(), jumpstream_densities.end(), 0.0);
    return total_density / jumpstream_densities.size();
}

// Function to calculate handstream difficulty
double Game::CalculateHandstreamDifficulty(const std::vector<std::vector<float>>& columns) {
    if (columns.size() < 3) return 0.0; // At least 3 columns are required for hands

    // Step 1: Identify hands (3 simultaneous notes across different columns)
    std::vector<float> hand_timings;
    for (size_t i = 0; i < columns.size(); ++i) {
        for (size_t j = i + 1; j < columns.size(); ++j) {
            for (size_t k = j + 1; k < columns.size(); ++k) {
                const auto& column1 = columns[i];
                const auto& column2 = columns[j];
                const auto& column3 = columns[k];

                size_t idx1 = 0, idx2 = 0, idx3 = 0;
                while (idx1 < column1.size() && idx2 < column2.size() && idx3 < column3.size()) {
                    float time1 = column1[idx1], time2 = column2[idx2], time3 = column3[idx3];

                    // Check if timings match (hands occur)
                    if (std::abs(time1 - time2) <= 1e-3 && std::abs(time2 - time3) <= 1e-3) {
                        hand_timings.push_back(time1);
                        ++idx1;
                        ++idx2;
                        ++idx3;
                    }
                    else {
                        // Increment the smallest index to keep searching
                        if (time1 < time2 || time1 < time3) 
                            ++idx1;
                        else if (time2 < time1 || time2 < time3) 
                            ++idx2;
                        else 
                            ++idx3;
                    }
                }
            }
        }
    }

    // Step 2: Sort hand timings
    std::sort(hand_timings.begin(), hand_timings.end());

    // Step 3: Identify handstreams (two consecutive hands with notes in between them)
    std::vector<double> handstream_densities;
    for (size_t i = 1; i < hand_timings.size(); ++i) {
        float start_hand = hand_timings[i - 1];
        float end_hand = hand_timings[i];

        // Check if the interval between hands is reasonable (e.g., ? 200ms)
        // Collect all note timings between the two hands
        std::vector<float> notes_between_hands;
        for (const auto& column : columns) {
            for (float note_time : column) {
                if (note_time > start_hand && note_time < end_hand) {
                    notes_between_hands.push_back(note_time);
                }
            }
        }

        // Calculate the density of the notes between the two hands
        double density = DetectInterval(notes_between_hands);
        handstream_densities.push_back(density);
    }

    // Step 4: Calculate average density of all handstreams
    if (handstream_densities.empty()) return 0.0;

    double total_density = std::accumulate(handstream_densities.begin(), handstream_densities.end(), 0.0);
    return total_density / handstream_densities.size();
}

// Function to calculate chordjack difficulty
double Game::CalculateChordjackDifficulty(const std::vector<std::vector<float>>& columns) {
    if (columns.empty()) return 0.0;

    // Step 1: Identify chords and jumpjacks (notes with 2 or more simultaneous hits)
    std::vector<float> chordjack_timings;

    for (size_t i = 0; i < columns.size(); ++i) {
        for (size_t j = i + 1; j < columns.size(); ++j) {
            const auto& column1 = columns[i];
            const auto& column2 = columns[j];

            size_t idx1 = 0, idx2 = 0;
            while (idx1 < column1.size() && idx2 < column2.size()) {
                float time1 = column1[idx1];
                float time2 = column2[idx2];

                // Check if timings match (within tolerance) for a jump/chord
                if (std::abs(time1 - time2) <= 1e-3) {
                    chordjack_timings.push_back(time1);
                    ++idx1;
                    ++idx2;
                }
                else if (time1 < time2) {
                    ++idx1;
                }
                else {
                    ++idx2;
                }
            }
        }
    }

    // Step 2: Add chords from 3 or more columns (if applicable)
    for (size_t i = 0; i < columns.size(); ++i) {
        for (size_t j = i + 1; j < columns.size(); ++j) {
            for (size_t k = j + 1; k < columns.size(); ++k) {
                const auto& column1 = columns[i];
                const auto& column2 = columns[j];
                const auto& column3 = columns[k];

                size_t idx1 = 0, idx2 = 0, idx3 = 0;
                while (idx1 < column1.size() && idx2 < column2.size() && idx3 < column3.size()) {
                    float time1 = column1[idx1];
                    float time2 = column2[idx2];
                    float time3 = column3[idx3];

                    // Check if timings match (within tolerance) for a chord
                    if (std::abs(time1 - time2) <= 1e-3 && std::abs(time2 - time3) <= 1e-3) {
                        chordjack_timings.push_back(time1);
                        ++idx1;
                        ++idx2;
                        ++idx3;
                    }
                    else {
                        // Increment the smallest index to keep searching
                        if (time1 < time2 || time1 < time3) ++idx1;
                        else if (time2 < time1 || time2 < time3) ++idx2;
                        else ++idx3;
                    }
                }
            }
        }
    }

    // Step 3: Sort and remove duplicates from chordjack timings
    std::sort(chordjack_timings.begin(), chordjack_timings.end());
    chordjack_timings.erase(std::unique(chordjack_timings.begin(), chordjack_timings.end()), chordjack_timings.end());

    // Step 4: Calculate the density of chordjacks using DetectInterval
    return DetectInterval(chordjack_timings);
}

// Function to calculate the strain of a chart
double Game::CalculateStrain(const std::vector<float>& note_timings) {
    if (note_timings.size() < 2) return 0.0;

    double total_strain = 0.0;
    float previous_interval = 0.0;
    float current_duration = 0.0;

    // Iterate through the note timings to identify consecutive intervals
    for (size_t i = 1; i < note_timings.size(); ++i) {
        float interval = note_timings[i] - note_timings[i - 1];

        // Check if the interval is consistent with the previous one (within tolerance)
        if (i == 1 || std::abs(interval - previous_interval) <= 1e-3) {
            current_duration += interval;
        }
        else {
            // Add the duration of the previous series to the total strain
            total_strain += current_duration;
            // Reset the duration for the new series
            current_duration = interval;
        }

        // Update the previous interval
        previous_interval = interval;
    }

    // Add the final series' duration to the total strain
    total_strain += current_duration;

    return total_strain;
}


// Main function to calculate the overall difficulty
double Game::CalculateDifficulty() {
    double interval = 0;
    double strain = 0;
    vector<vector<float>> note_columns;
    for (int i = 0; i < 4; i++) {
        note_columns.push_back(mNoteColumns[i].hitTimes);
        note_columns.push_back(mNoteColumns[i].longNoteHitTimes);
        interval += DetectInterval(mNoteColumns[i].hitTimes);
        interval += DetectInterval(mNoteColumns[i].longNoteHitTimes);
        strain += CalculateStrain(mNoteColumns[i].hitTimes);
        strain += CalculateStrain(mNoteColumns[i].longNoteHitTimes);
    }

    double jumpstream_difficulty = CalculateJumpstreamDifficulty(note_columns);
    double handstream_difficulty = CalculateHandstreamDifficulty(note_columns);
    double chordjack_difficulty = CalculateChordjackDifficulty(note_columns);

    jumpstream_difficulty = jumpstream_difficulty != 0 ? 1 / jumpstream_difficulty : 0;
    handstream_difficulty = handstream_difficulty != 0 ? 1 / handstream_difficulty : 0;
    chordjack_difficulty = chordjack_difficulty != 0 ? 1 / chordjack_difficulty : 0;

    double speed_difficulty = (1.0 / (interval / 1000)) / 4.0 * 1000;
    double strain_difficulty = mCurrentSongDuration / (strain / 4.0);
    
    // Calculate final difficulty as the average of all pattern difficulties
    double final_difficulty = (jumpstream_difficulty + handstream_difficulty + chordjack_difficulty) / 3.0f + speed_difficulty * strain_difficulty;
     
    printf("Jumpstream Difficulty: %.2f\n", jumpstream_difficulty);
    printf("Handstream Difficulty: %.2f\n", handstream_difficulty);
    printf("Chordjack Difficulty: %.2f\n", chordjack_difficulty);
    printf("Speed: %.2f\n", speed_difficulty);
    printf("Strain %.2f\n", strain_difficulty);

    return final_difficulty;    
}
