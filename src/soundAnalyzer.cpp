//
// Created by PGD384 on 7/9/2020.
//

#include "soundAnalyzer.h"
#include <math.h>

Sound SoundAnalyzer::processSample(int sample) {
    if (!isSilenceLevelSet()){
        initializeSilenceLevel(sample);
        return Sound::unknown;
    }
    if (sample == silenceLevel)
        return Sound::silence;
    else
        return Sound::unknown;
}

bool SoundAnalyzer::isSilenceLevelSet() {
    return silenceInitialized;
}

void SoundAnalyzer::initializeSilenceLevel(int sample) {
    if (!isSilenceLevelSet()){
        silenceLevelSampleCount++;
        silenceLevel += sample;
        if (itsTheLastSilenceInitSample())
            setSilenceLevel();
    }
}

void SoundAnalyzer::setSilenceLevel() {
    silenceInitialized = true;
    silenceLevel = nearbyint ((silenceLevel) / silenceLevelSampleCount);
}

bool SoundAnalyzer::itsTheLastSilenceInitSample() const { return silenceLevelSampleCount == numberOfInitSamplesNeeded; }
