//
// Created by PGD384 on 7/10/2020.
//

#include <math.h>
#include "SoundLevel.h"

Sound SoundLevel::processInput(int input) {
    resetSampleIfAlreadyProcessed();
    sample->processInput(input);
    if (sample->isComplete())
        return processSample(sample);
    return Sound::unknown;
}

Sound SoundLevel::processSample(SoundSample *sample) {
    if (!isLevelSet()) {
        setLevel(sample->getLevel());
        return Sound::unknown;
    }
    if (isSampleAtLevel(sample))
        return sound;
    return processSampleAtNextLevel(sample);
}


void SoundLevel::resetSampleIfAlreadyProcessed() {
    if (sample->isComplete()) {
        delete sample;
        sample = new SoundSample();
    }
}

bool SoundLevel::isSampleAtLevel(SoundSample *sample) const {
    double precision = (double) level * ((double)precisionPercent/(double)100);
    return fabs(double(sample->getLevel() - level)) <= precision;
}

bool SoundLevel::isLevelSet() const { return level != levelNotSet; }

int SoundLevel::setLevel(int level) { return SoundLevel::level = level; }

void SoundLevel::setNextLevel(SoundLevel *nextLevel) { SoundLevel::nextLevel = nextLevel; }

int SoundLevel::getLevel() const { return level; }

Sound SoundLevel::processSampleAtNextLevel(SoundSample *sample) {
    if (nextLevel)
        return nextLevel->processSample(sample);
    return Sound::unknown;
}



