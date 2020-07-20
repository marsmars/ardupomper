//
// Created by PGD384 on 7/20/2020.
//

#include <Arduino.h>
#include <Logger.h>
#include "LoopProcessor.h"


LoopProcessor::LoopProcessor(Pomper *pomper, SoundAnalyzer *analyzer, Leds *leds) : pomper(pomper),
                                                                                    analyzer(analyzer),
                                                                                    leds(leds) {}
void LoopProcessor::stepPomperBack() { pomper->stepBack(); }

void LoopProcessor::changeLedsStates() const { leds->changeStates(); }

void LoopProcessor::processInput() {
    Sound sound = analyzer->processInput(analogRead(A0));
    changeLedsStates();
    printInitializedLevels();
    processSound(sound);
}

void LoopProcessor::printInitializedLevels() const {
    static bool silencePrinted = false;
    static bool failurePrinted = false;
    static bool normalPrinted = false;

    if (analyzer->isSilenceLevelSet() && !silencePrinted) {
        Logger::log("--Silence level:");
        Logger::log(analyzer->getSilenceLevel());
        silencePrinted = true;
    }
    if (analyzer->isFailureLevelSet() && !failurePrinted) {
        Logger::log("--Failure level:");
        Logger::log(analyzer->getFailureLevel());
        failurePrinted = true;
    }
    if (analyzer->isNormalLevelSet() && !normalPrinted) {
        Logger::log("--Normal level:");
        Logger::log(analyzer->getNormalLevel());
        normalPrinted = true;
    }
}

void LoopProcessor::processSound(Sound sound) {
    if (analyzer->isInitialized())
        switch (sound) {
            case Sound::silence:
                Logger::log("Silence detected");
                break;
            case Sound::failure:
                Logger::log("Failure detected");
                pomper->revolve();
                break;
            case Sound::normal:
                Logger::log("Normal sound detected");
                break;
            case Sound::unknown:
                break;
        };
}

