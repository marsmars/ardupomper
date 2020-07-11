//
// Created by PGD384 on 7/10/2020.
//

#include "SoundSample.h"
#include "SoundLevel.h"
#include <math.h>

bool SoundSample::isProcessed() { return isLastInputInSample(); }

bool SoundSample::isLastInputInSample() const { return inputCount == sampleSize; }

int SoundSample::getAverage(int sum, int count) const { return nearbyint((double)sum / (double)count); }

int SoundSample::processInput(int input) {
    inputCount++;
    inputLevel += input;
    if (isLastInputInSample())
        return getAverage(inputLevel, inputCount);
    return notProcessed;
}