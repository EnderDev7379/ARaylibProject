#include "raylib.h"

// Structure declarations and definitions
//------------------------------------------------------------------------------------------

// struct Timer varName = {when timer starts in seconds, when timer stops in seconds}
// It is recommended to use the NewTimer function to create a new Timer instead of the line above
struct Timer {
    float startTime;
    float endTime;
    float time;
};
//------------------------------------------------------------------------------------------

// Function declarations
//------------------------------------------------------------------------------------------

struct Timer NewTimer(float startTime, float endTime);
bool UpdateTimer(struct Timer *timer);
//------------------------------------------------------------------------------------------

// Function defenitions
//------------------------------------------------------------------------------------------

// Creates a new timer structure
struct Timer NewTimer(float startTime, float endTime) {
    struct Timer timer;
    timer.startTime = startTime;
    timer.endTime = endTime;
    return timer;
}

// Updates timer 
// This function should be called once every frame for every timer
bool UpdateTimer(struct Timer *timer) {
    if (timer->startTime <= GetTime()) timer->time += GetFrameTime();
    return timer->time >= timer->endTime;
}

// Prototype functions
/*
bool * UpdateTimer(struct Timer *timers[]) {
    int n = sizeof(timers) / sizeof(timers[0]);
    bool timersDone[n];
    for (int i = 0; i < n; i++) {
        if (timers[i]->startTime <= GetTime()) timers[i]->time += GetFrameTime();
        timersDone[i] = timers[i]->time >= timers[i]->endTime;
    }
    return *timersDone;
}
*/
//------------------------------------------------------------------------------------------
