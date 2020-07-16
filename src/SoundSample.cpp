//
// Created by PGD384 on 7/10/2020.
//

#include <math.h>
#include "SoundSample.h"
#include "SoundLevel.h"
#include "Logger.h"

bool SoundSample::isComplete() { return isLastInputInSample(); }

bool SoundSample::isLastInputInSample() const { return inputCount == sampleSize; }

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
    if (isLastInputInSample()) {
//        Logger::log("Sample level:");
        sampleLevel = getAverage(inputLevel, inputCount / 4);
        return inputLevel;
    }
    return notProcessed;
}

double SoundSample::getLevel() {
    return sampleLevel;
}