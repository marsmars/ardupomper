//
// Created by PGD384 on 7/10/2020.
//

#include <math.h>
#include "SoundLevel.h"

bool SoundLevel::isSampleProcessed(int &input) {
    inputCount++;
    inputLevel += input;
    if (isLastInputInSample(inputCount)) {
        input = getAverage(inputLevel, inputCount);
        inputCount = 0;
        inputLevel = 0;
        return true;
    }
    return false;
}

bool SoundLevel::isLastInputInSample(int inputCount) const { return inputCount == sampleSize; }

int SoundLevel::getAverage(int sum, int count) const { return nearbyint((double)sum / (double)count); }

bool SoundLevel::processInput(int input) {
    bool sampleAtLevel = false;
    if (isSampleProcessed(input))
        if(isLevelSet())
            sampleAtLevel = isSampleAtLevel(input);
        else
            setLevel(input);
    return sampleAtLevel;
}

bool SoundLevel::isSampleAtLevel(int sample) const { return sample == level; }

bool SoundLevel::isLevelSet() const {
    return level != levelNotSet;
}

int SoundLevel::getLevel() const {
    return level;
}

void SoundLevel::setLevel(int level) {
    SoundLevel::level = level;
}
