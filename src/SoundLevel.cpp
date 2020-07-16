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
//    double precision = (double) level * ((double) precisionPercent / (double) 100);
//    return fabs(double(sample->getLevel() - level)) <= precision;
    return fabs(double(sample->getLevel() - level)) <= 0.5;
}

bool SoundLevel::isLevelSet() const { return level != levelNotSet; }

double SoundLevel::setLevel(double level) { return SoundLevel::level = level; }

void SoundLevel::setNextSoundLevel(SoundLevel *nextLevel) { SoundLevel::nextLevel = nextLevel; }

double SoundLevel::getLevel() const { return level; }

Sound SoundLevel::processSampleAtNextLevel(SoundSample *sample) {
    if (nextLevel)
        return nextLevel->processSample(sample);
    return Sound::unknown;
}



