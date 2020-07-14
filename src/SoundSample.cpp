//
// Created by PGD384 on 7/10/2020.
//

#include <math.h>
#include "SoundSample.h"
#include "SoundLevel.h"
#include "Logger.h"

bool SoundSample::isComplete() { return isLastInputInSample(); }

bool SoundSample::isLastInputInSample() const { return inputCount == sampleSize; }

int SoundSample::getAverage(unsigned long sum, int count) const {
    return round((double)sum / (double)count);
}

int SoundSample::processInput(int input) {
    inputCount++;
    inputLevel += input;
    if (isLastInputInSample())
        return inputLevel = getAverage(inputLevel, inputCount);
    return notProcessed;
}

int SoundSample::getLevel() {
    return inputLevel;
}
