//
// Created by PGD384 on 7/10/2020.
//

#include <math.h>
#include "SoundSample.h"
#include "SoundLevel.h"
#include "Logger.h"

bool SoundSample::isComplete() { return isLastInputInSample(); }

bool SoundSample::isLastInputInSample() const { return inputCount == sampleSize; }

double SoundSample::getLevel() const { return sampleLevel; }

bool SoundSample::isAtLevel(double level) const {
    double precision = (double) level * ((double) precisionPercent / (double) 100);
    return fabs(double(getLevel() - level)) <= precision;
}

double SoundSample::getAverage(unsigned long sum, int count) const {
    return (double)sum / (double)count;
}

double SoundSample::processInput(int input) {
    inputCount++;
    if (inputCount < sampleSize /2)
        inputLevel += input;
    else if (inputCount == sampleSize /2){
        inputLevel += input;
        baseLevel = getAverage(inputLevel, inputCount);
        inputLevel = 0;
    }
    else
        inputLevel += fabs((double )input-baseLevel);
    return setSampleLevel();
}

double SoundSample::setSampleLevel() {
    if (isLastInputInSample()) {
        return sampleLevel = getAverage(inputLevel, inputCount / 4);
    }
    return notProcessed;
}

