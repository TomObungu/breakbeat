#include "Game.hpp"

double Game::DetectInterval(const vector<float>& note_times, int tolerance = 5) 
{
    if (note_times.size() < 2) return false;
    
    vector<float> intervals;
    for (unsigned i = 1; i < note_times.size(); ++i) {
        intervals.push_back(note_times[i] - note_times[i - 1]);
    }

    return std::accumulate(intervals.begin(), intervals.end(), 0.0) / intervals.size();
}

// Function to calculate difficulty based on streams, jumps, and chordjacks
double Game::CalculateDifficulty() {
    double interval = 0.0f;
    double difficulty = 0.0f;

    for (int i = 0; i < 4; i++)
    {
        interval += DetectInterval(mNoteColumns[i].hitTimes);
    }

    return difficulty = 1 / interval / 4.0f ;
}