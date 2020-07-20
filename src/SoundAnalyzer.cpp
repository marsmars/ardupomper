//
// Created by PGD384 on 7/9/2020.
//

#include "SoundAnalyzer.h"
#include "SoundLevel.h"

SoundAnalyzer::SoundAnalyzer() : silence{new SoundLevel(Sound::silence)},
                                 failure{new SoundLevel(Sound::failure)},
                                 normal{new SoundLevel(Sound::normal)}{
    silence->setNextSoundLevel(failure);
    failure->setNextSoundLevel(normal);
}

SoundAnalyzer::~SoundAnalyzer() {
    delete normal;
    delete failure;
    delete silence;
}

Sound SoundAnalyzer::processInput(int input) {
    return silence->processInput(input);
}

bool SoundAnalyzer::isSilenceLevelSet() const { return silence->isLevelSet(); }

bool SoundAnalyzer::isFailureLevelSet() const { return failure->isLevelSet(); }

bool SoundAnalyzer::isNormalLevelSet() const { return normal->isLevelSet(); }

double SoundAnalyzer::getSilenceLevel() const {
    return silence->getLevel();
}

double SoundAnalyzer::getFailureLevel() const {
    return failure->getLevel();
}

double SoundAnalyzer::getNormalLevel() const {
    return normal->getLevel();
}

bool SoundAnalyzer::isInitialized() const {
    return isSilenceLevelSet() && isFailureLevelSet() && isNormalLevelSet();
}



