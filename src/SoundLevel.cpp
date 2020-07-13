//
// Created by PGD384 on 7/10/2020.
//

#include <math.h>
#include "SoundLevel.h"

Sound SoundLevel::processInput(int input) {
    resetSampleIfAlreadyProcessed();
    int sampleLevel = sample->processInput(input);
    if (!isLevelSet())
        return setLevelIfSampleProcessed(sampleLevel);
    return processAtLevel(input, sampleLevel);
}

Sound SoundLevel::processAtLevel(int input, int sampleLevel) const {
    if (sample->isProcessed() && isSampleAtLevel(sampleLevel))
        return sound;
    else
        return processNextLevel(input);
}

Sound SoundLevel::setLevelIfSampleProcessed(int sampleLevel) {
    if (sample->isProcessed())
        setLevel(sampleLevel);
    return Sound::unknown;
}

Sound SoundLevel::processNextLevel(int input) const {
    if (nextLevel)
        return nextLevel->processInput(input);
    return Sound::unknown;
}

void SoundLevel::resetSampleIfAlreadyProcessed() {
    if (sample->isProcessed()) {
        delete sample;
        sample = new SoundSample();
    }
}

bool SoundLevel::isSampleAtLevel(int sample) const {
    double precision = (double) level * ((double)precisionPercent/(double)100);
    return fabs(double(sample - level)) <= precision;
}

bool SoundLevel::isLevelSet() const { return level != levelNotSet; }

int SoundLevel::setLevel(int level) { return SoundLevel::level = level; }

bool SoundLevel::isSampleProcessed() const { return sample->isProcessed(); }

void SoundLevel::setNextLevel(SoundLevel *nextLevel) { SoundLevel::nextLevel = nextLevel; }

int SoundLevel::getLevel() const { return level; }

