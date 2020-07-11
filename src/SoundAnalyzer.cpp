//
// Created by PGD384 on 7/9/2020.
//

#include "SoundAnalyzer.h"
#include "SoundLevel.h"

SoundAnalyzer::SoundAnalyzer() : silence{new SoundLevel(Sound::silence)},
                                 failure{new SoundLevel(Sound::failure)} {
    silence->setNextLevel(failure);

}

Sound SoundAnalyzer::processInput(int input) {
    return silence->processInput(input);
}

bool SoundAnalyzer::isSilenceLevelSet() const { return silence->isLevelSet(); }

bool SoundAnalyzer::isFailureLevelSet() const { return failure->isLevelSet(); }


