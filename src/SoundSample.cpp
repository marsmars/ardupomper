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

bool SoundSample::isAtLevel(int level) const {
//    double precision = (double) level * ((double) precisionPercent / (double) 100);
//    return fabs(double(sample->getLevel() - level)) <= precision;
    return fabs(double(getLevel() - level)) <= 0.5;
}

double SoundSample::getAverage(unsigned long sum, int count) const {
//    Logger::log((double)sum / (double)count);
    return (double)sum / (double)count;
}

int SoundSample::processInput(int input) {
    inputCount++;
    if (inputCount < sampleSize /2)
        inputLevel += input;
    else if (inputCount == sampleSize /2){
        inputLevel += input;
//        Logger::log("Base level:");
        baseLevel = getAverage(inputLevel, inputCount);
        inputLevel = 0;
    }
    else
        inputLevel += fabs(input-baseLevel);
    return setSampleLevel();
}

int SoundSample::setSampleLevel() {
    if (isLastInputInSample()) {
//        Logger::log("Sample level:");
        return sampleLevel = getAverage(inputLevel, inputCount / 4);
    }
    return notProcessed;
}

