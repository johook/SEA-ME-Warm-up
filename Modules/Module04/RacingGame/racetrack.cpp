#include "racetrack.h"

RaceTrack::RaceTrack(int size)
    : size(size), finishLine(size) {}

int RaceTrack::getFinishLine() const {
    return finishLine;
}
