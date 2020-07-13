//
// Created by PGD384 on 7/11/2020.
//

#include <Arduino.h>
#include "Leds.h"

void ledsSetup() {
    pinMode(silenceLed, OUTPUT);
    pinMode(failureLed, OUTPUT);
    pinMode(normalLed, OUTPUT);
}

void Leds::changeStates() {
    digitalWrite(silenceLed, analyzer->isSilenceLevelSet() ? HIGH : LOW);
    digitalWrite(failureLed, analyzer->isFailureLevelSet() ? HIGH : LOW);
    digitalWrite(normalLed, analyzer->isNormalLevelSet() ? HIGH : LOW);
}

Leds::Leds(SoundAnalyzer *analyzer) : analyzer(analyzer) {}
