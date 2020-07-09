//
// Created by PGD384 on 7/9/2020.
//

#include "soundAnalyzer.h"
#include <math.h>

Sound SoundAnalyzer::processInput(int input) {
    if (!isSilenceLevelSet()) {
        initializeSilenceLevel(input);
        return Sound::unknown;
    }
    return getSoundFromInput(input);
}

Sound SoundAnalyzer::getSoundFromInput(int input) const {
    Sound result = Sound::unknown;

    if(isSampleProcessed(input))
        result = getSound(input);
    return result;
}

bool SoundAnalyzer::isSampleProcessed(int &input) const {
    static int inputCount = 0;
    static int inputLevel = 0;
    inputCount++;
    inputLevel += input;
    if (inputCount == sampleSize) {
        input = getAverage(inputLevel, inputCount);
        inputCount = 0;
        inputLevel = 0;
        return true;
    }
    return false;
}

Sound SoundAnalyzer::getSound(int inputLevel) const { return isSampleSilence(inputLevel) ? Sound::silence : Sound::unknown; }

int SoundAnalyzer::getAverage(int sum, int count) const { return nearbyint(sum / count); }

bool SoundAnalyzer::isSampleSilence(int sample) const { return sample == silenceLevel; }

bool SoundAnalyzer::isSilenceLevelSet() const { return itsTheLastSilenceInitReading(); }

void SoundAnalyzer::initializeSilenceLevel(int input) {
    silenceLevelInputCount++;
    silenceLevel += input;
    if (itsTheLastSilenceInitReading())
        setSilenceLevel();
}

bool SoundAnalyzer::itsTheLastSilenceInitReading() const { return silenceLevelInputCount == silenceInitSampleSize; }

void SoundAnalyzer::setSilenceLevel() {
    silenceLevel = getAverage(silenceLevel, silenceLevelInputCount);
}
