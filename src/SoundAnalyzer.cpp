//
// Created by PGD384 on 7/9/2020.
//

#include "SoundAnalyzer.h"
#include "SoundLevel.h"

Sound SoundAnalyzer::processInput(int input) {
    Sound result = Sound::unknown;
    if (silence->isLevelSet()) {
        if (silence->processInput(input)) {
            result = Sound::silence;
        } else if (failure->isLevelSet()) {
            if (failure->processInput(input))
                result = Sound::failure;
        } else
            failure->processInput(input);
    } else
        silence->processInput(input);

    return result;
}

bool SoundAnalyzer::isSilenceLevelSet() const { return silence->isLevelSet(); }

bool SoundAnalyzer::isFailureLevelSet() const { return failure->isLevelSet(); }

